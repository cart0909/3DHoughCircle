#ifndef HOUGHCIRCLE_H
#define HOUGHCIRCLE_H
#include <map>
#include <iostream>
#include <unordered_map>
#include <functional>
#include "createcirclepointcloud.h"

class RCenter {
public:
    friend bool operator<(const RCenter& lhs, const RCenter& rhs);
    friend bool operator==(const RCenter& lhs, const RCenter& rhs);
    friend std::hash<RCenter>;

    RCenter(float r, float cx, float cy, float cz) {
        _r = r;
        _gridx = cx/res;
        _gridy = cy/res;
        _gridz = cz/res;
    }

    inline bool operator<(const RCenter& rhs)
    {
        if(_r != rhs._r)
            return _r < rhs._r;
        else if(_gridx != rhs._gridx)
            return _gridx < rhs._gridx;
        else if(_gridy != rhs._gridy)
            return _gridy < rhs._gridy;
        return _gridz < rhs._gridz;
    }

    static float res;
    float _r;
    int _gridx;
    int _gridy;
    int _gridz;
};

inline bool operator<(const RCenter& lhs, const RCenter& rhs) {
    if(lhs._r != rhs._r)
        return lhs._r < rhs._r;
    else if(lhs._gridx != rhs._gridx)
        return lhs._gridx < rhs._gridx;
    else if(lhs._gridy != rhs._gridy)
        return lhs._gridy < rhs._gridy;
    return lhs._gridz < rhs._gridz;
}

inline bool operator==(const RCenter& lhs, const RCenter& rhs) {
    return (lhs._r == rhs._r) && (lhs._gridx==rhs._gridx) && (lhs._gridy==rhs._gridy) && (lhs._gridz == rhs._gridz);
}

namespace std {
template<>
class hash<RCenter> {
public:
    size_t operator()(const RCenter& obj) const {
        return hash<float>()(obj._r) ^ hash<int>()(obj._gridx) ^ hash<int>()(obj._gridy) ^ hash<int>()(obj._gridz);
    }
};
}

class HoughCircle
{
public:
    HoughCircle();
    HoughCircle(float rmin, float rmax, float rres, float thres, float phires) :
        _rmin(rmin), _rmax(rmax), _rres(rres), _thres(thres), _phires(phires)
    {

    }

    using Accumulator = std::map<RCenter, int>;

    void transform(const Vector3fs& points, Accumulator& accu) {
        for(const auto& eachPoint : points) {
            for(float r = _rmin; r <= _rmax; r += _rres) {
                for(float th = 0.0f; th <= 2.0f*M_PI; th+= _thres) {
                    for(float phi = 0.0f; phi <= M_PI; phi += _phires) {
                        auto cx = eachPoint(0) - r*cos(th)*sin(phi);
                        auto cy = eachPoint(1) - r*sin(th)*sin(phi);
                        auto cz = eachPoint(2) - r*cos(phi);
                        accu[RCenter(r, cx, cy, cz)]++;
                    }
                }
            }
        }
    }

    float _rmin, _rmax;
    float _rres, _thres, _phires;
};

#endif // HOUGHCIRCLE_H
