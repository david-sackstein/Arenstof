#pragma once

#include <ostream>

class ArenstofPoint
{
public:

    ArenstofPoint(
            long double x,
            long double y,
            long double vx,
            long double vy);

    long double getX() const { return _x; }
    long double getY() const { return _y; }
    long double getVX() const { return _vx; }
    long double getVY() const { return _vy; }

    friend std::ostream& operator <<(std::ostream &os, const ArenstofPoint& p);

private:

    long double _x;
    long double _y;
    long double _vx;
    long double _vy;
};
