#ifndef CREATECIRCLEPOINTCLOUD_H
#define CREATECIRCLEPOINTCLOUD_H
#include <random>
#include <vector>
#include <cmath>
#include "util.h"

class CreateCirclePointCloud
{
public:
    CreateCirclePointCloud();
    CreateCirclePointCloud(float r, float cx, float cy, float cz);

    std::vector<Point3> generatePoints(int nums) const;

    float _r;
    float _cx, _cy, _cz;
};

#endif // CREATECIRCLEPOINTCLOUD_H
