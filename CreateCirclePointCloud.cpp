#include "CreateCirclePointCloud.h"

CreateCirclePointCloud::CreateCirclePointCloud()
{

}

CreateCirclePointCloud::CreateCirclePointCloud(float r, float cx, float cy, float cz) :
    _r(r), _cx(cx), _cy(cy), _cz(cz)
{

}

std::vector<Point3> CreateCirclePointCloud::generatePoints(int nums) const {
    std::vector<Point3> points;
    points.resize(nums);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> thDis(0, 2*M_PI), phiDis(0, M_PI);

    for(int i = 0; i < nums; ++i) {
        float x, y, z;
        float th, phi;

        th = static_cast<float>(thDis(gen));
        phi = static_cast<float>(phiDis(gen));

        points[i].x = _cx + _r*cos(th)*sin(phi);
        points[i].y = _cy + _r*sin(th)*sin(phi);
        points[i].z = _cz + _r*cos(phi);
    }

    return points;
}
