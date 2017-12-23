#pragma once
#include <ostream>

class ArenstorfPoint
{
public:

    ArenstorfPoint();

    ArenstorfPoint(
            long double x,
            long double y,
            long double vx,
            long double vy);

    long double getX() const { return _x; }
    long double getY() const { return _y; }
    long double getVX() const { return _vx; }
    long double getVY() const { return _vy; }

    friend std::ostream& operator <<(std::ostream &os, const ArenstorfPoint& p);

    void Update(long double ax, long double ay, long double dt);

private:

    long double _x;
    long double _y;
    long double _vx;
    long double _vy;
};
