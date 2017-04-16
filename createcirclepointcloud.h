#ifndef CREATECIRCLEPOINTCLOUD_H
#define CREATECIRCLEPOINTCLOUD_H
#include <random>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using Vector3fs = std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> >;

class CreateCirclePointCloud
{
public:
    CreateCirclePointCloud();
    CreateCirclePointCloud(float r, float cx, float cy, float cz);

    Vector3fs generatePoints(int nums) {
        Vector3fs points;
        points.resize(nums);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> thDis(0, 2*M_PI), phiDis(0, M_PI);

        for(int i = 0; i < nums; ++i) {
            float x, y, z;
            float th, phi;

            th = static_cast<float>(thDis(gen));
            phi = static_cast<float>(phiDis(gen));

            x = _cx + _r*cos(th)*sin(phi);
            y = _cy + _r*sin(th)*sin(phi);
            z = _cz + _r*cos(phi);

            points[i] << x, y, z;
        }

        return points;
    }

    float _r;
    float _cx, _cy, _cz;
};

#endif // CREATECIRCLEPOINTCLOUD_H
