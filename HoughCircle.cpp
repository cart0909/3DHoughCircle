#include "HoughCircle.h"

float RCenter::res = 2.5f;

RCenter::RCenter(float r, float cx, float cy, float cz) {
    _r = r;
    _gridx = cx/res;
    _gridy = cy/res;
    _gridz = cz/res;
}

bool RCenter::operator<(const RCenter& rhs){
    if(_r != rhs._r)
        return _r < rhs._r;
    else if(_gridx != rhs._gridx)
        return _gridx < rhs._gridx;
    else if(_gridy != rhs._gridy)
        return _gridy < rhs._gridy;
    return _gridz < rhs._gridz;
}

bool operator<(const RCenter& lhs, const RCenter& rhs) {
    if(lhs._r != rhs._r)
        return lhs._r < rhs._r;
    else if(lhs._gridx != rhs._gridx)
        return lhs._gridx < rhs._gridx;
    else if(lhs._gridy != rhs._gridy)
        return lhs._gridy < rhs._gridy;
    return lhs._gridz < rhs._gridz;
}

bool operator==(const RCenter& lhs, const RCenter& rhs) {
    return (lhs._r == rhs._r) && (lhs._gridx==rhs._gridx) && (lhs._gridy==rhs._gridy) && (lhs._gridz == rhs._gridz);
}

HoughCircle::HoughCircle()
{

}

