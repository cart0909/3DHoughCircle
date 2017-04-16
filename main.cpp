#include <iostream>
#include <chrono>
#include "CreateCirclePointCloud.h"
#include "HoughCircle.h"
using namespace std;

int main(int argc, char *argv[])
{
    CreateCirclePointCloud pointCloudGenerator(35,-42.6,87.87,-68.9);
    auto points = pointCloudGenerator.generatePoints(4000);

    HoughCircle houghCircle(30, 40, 1, 10*M_PI/180, 10*M_PI/180, 2.5f);
    HoughCircle::Accumulator accu;

    auto t0 = std::chrono::steady_clock::now();
    houghCircle.transform(points, accu);
    auto t1 = std::chrono::steady_clock::now();
    cout << std::chrono::duration_cast<std::chrono::milliseconds>((t1-t0)).count()*0.001 << " (s)" << endl;

#if USE_OLD
    auto maxIt = accu.end();
    int maxCount = -1;

    for(auto it = accu.begin(); it != accu.end(); ++it) {
        if(it->second > maxCount) {
            maxCount = it->second;
            maxIt = it;
        }
    }

    cout << "maxCount: " << maxCount << endl;
    cout << "r: " << maxIt->first._r << " cx: " << maxIt->first._gridx*RCenter::res << " cy: " << maxIt->first._gridy*RCenter::res <<
            " cz: " << maxIt->first._gridz*RCenter::res << " num:" << maxIt->second << endl;
#else
    accu.report();
#endif
    return 0;
}
