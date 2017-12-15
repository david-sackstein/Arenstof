#include "ArenstofPoint.h"

ArenstofPoint::ArenstofPoint(
        long double x,
        long double y,
        long double vx,
        long double vy)
        :
        _x(x),
        _y(y),
        _vx(vx),
        _vy(vy)
{
}

std::ostream& operator << (std::ostream &os, const ArenstofPoint& p)
{
    os << "(" << p._x << ", " << p._y << ")";
    return os;
}

