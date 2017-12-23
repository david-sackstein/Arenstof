#include <iostream>
#include "ArenstorfPoint.h"

ArenstorfPoint::ArenstorfPoint() :
    _x(0),
    _y(0),
    _vx(0),
    _vy(0)
{
}

ArenstorfPoint::ArenstorfPoint(
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

void ArenstorfPoint::Update(long double ax, long double ay, long double dt)
{
    _x = _x + _vx * dt;
    _y = _y + _vy * dt;
    _vx = _vx + ax * dt;
    _vy = _vy + ay * dt;
}

std::ostream& operator << (std::ostream &os, const ArenstorfPoint& p)
{
    //os << "(" << p._x << ", " << p._y << ")";
    std::cout.precision(5);
    os << p._x << ", " <<  p._y;
    return os;
}

