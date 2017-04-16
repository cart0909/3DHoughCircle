#ifndef HOUGHCIRCLE_H
#define HOUGHCIRCLE_H
#include <map>
#include <iostream>
#include <unordered_map>
#include <functional>
#include "CreateCirclePointCloud.h"
#include "util.h"

#ifndef USE_OLD
#define USE_OLD 0
#endif

class RCenter {
public:
    friend bool operator<(const RCenter& lhs, const RCenter& rhs);
    friend bool operator==(const RCenter& lhs, const RCenter& rhs);
    friend std::hash<RCenter>;

    RCenter(float r, float cx, float cy, float cz);

    bool operator<(const RCenter& rhs);

    static float res;
    float _r;
    int _gridx;
    int _gridy;
    int _gridz;
};
// for map
bool operator<(const RCenter& lhs, const RCenter& rhs);
// for hash, but hmm.. very slow...
bool operator==(const RCenter& lhs, const RCenter& rhs);
namespace std {
template<>
class hash<RCenter> {
public:
    size_t operator()(const RCenter& obj) const {
        return hash<float>()(obj._r) ^ hash<int>()(obj._gridx) ^ hash<int>()(obj._gridy) ^ hash<int>()(obj._gridz);
    }
};
}
// end RCenter

class HoughCircle
{
public:
    HoughCircle();
#if USE_OLD
    HoughCircle(float rmin, float rmax, float rres, float thres, float phires, float gridres) :
        _rmin(rmin), _rmax(rmax), _rres(rres), _thres(thres), _phires(phires)
    {
        RCenter::res = gridres;
    }
    using Accumulator = std::map<RCenter, int>;

    void transform(const std::vector<Point3>& points, Accumulator& accu) {
        for(const auto& eachPoint : points) {
            for(float r = _rmin; r <= _rmax; r += _rres) {
                for(float th = 0.0f; th <= 2.0f*M_PI; th+= _thres) {
                    for(float phi = 0.0f; phi <= M_PI; phi += _phires) {
                        auto cx = eachPoint.x - r*cos(th)*sin(phi);
                        auto cy = eachPoint.y - r*sin(th)*sin(phi);
                        auto cz = eachPoint.z - r*cos(phi);
                        accu[RCenter(r, cx, cy, cz)]++;
                    }
                }
            }
        }
    }
#else
    HoughCircle(float rmin, float rmax, float rres, float thres, float phires, float gridres) :
        _rmin(rmin), _rmax(rmax), _gridres(gridres), _rres(rres), _thres(thres), _phires(phires)
    {

    }

    class Accumulator {
    public:
        friend HoughCircle;
        Accumulator():bestRIdx(-1.0f), bestGridxIdx(-1), bestGridyIdx(-1), bestGridzIdx(-1), maxCount(0), _gridresPtr(nullptr)
        {}

        void insert(float* gridresPtr, float r, float cx, float cy, float cz) {
            if(_gridresPtr != gridresPtr)
                _gridresPtr = gridresPtr;
            auto invGridRes = 1.0f/(*_gridresPtr);
            int gridx = cx*invGridRes, gridy = cy*invGridRes, gridz = cz*invGridRes;
            int countNum = ++_accumulator[r][gridx][gridy][gridz];
            if(countNum > maxCount) {
                maxCount = countNum;
                bestRIdx = r;
                bestGridxIdx = gridx;
                bestGridyIdx = gridy;
                bestGridzIdx = gridz;
            }
        }

        void report() {
            auto gridres = *_gridresPtr;
            std::cout << "r: " << bestRIdx << " cx: " << bestGridxIdx*gridres << " cy:" << bestGridyIdx*gridres <<
                         " cz: " << bestGridzIdx*gridres << " count: " << maxCount << std::endl;
        }

        float bestRIdx;
        int bestGridxIdx, bestGridyIdx, bestGridzIdx;
        int maxCount;
        float* _gridresPtr;
        std::map<float, std::map<int, std::map<int, std::map<int, int>>>> _accumulator;
    };

    void transform(const std::vector<Point3>& points, Accumulator& accu) {
        for(const auto& eachPoint : points) {
            for(float r = _rmin; r <= _rmax; r += _rres) {
                for(float th = 0.0f; th <= 2.0f*M_PI; th+= _thres) {
                    for(float phi = 0.0f; phi <= M_PI; phi += _phires) {
                        auto cx = eachPoint.x - r*cos(th)*sin(phi);
                        auto cy = eachPoint.y - r*sin(th)*sin(phi);
                        auto cz = eachPoint.z - r*cos(phi);
                        accu.insert(&_gridres, r, cx, cy, cz);
                    }
                }
            }
        }
    }
#endif

    float _rmin, _rmax, _gridres;
    float _rres, _thres, _phires;
};

#endif // HOUGHCIRCLE_H
