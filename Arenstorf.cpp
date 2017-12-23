#include <cmath>
#include "Arenstorf.h"

using namespace std;


/**
 * This file represents an arenstorf. Holds calculate methods which calculate the acceleration and
 * location
 * of the ship at each time unit.
 */

/**
 * Arenstorf constructor.
 * @param init the first point of the ship .
 * @param n number of times to calculate
 * @param dt
 */
Arenstorf::Arenstorf(
    const ArenstorfPoint &initialPoint,
    unsigned int n,
    long double dt)
    :
    _point(initialPoint),
    _n(n),
    _dt(dt)
{
}

void Arenstorf::computePoints(ArenstorfPoint *points, unsigned int m) {

    unsigned int pointIndex = 0;

    for (unsigned int i = 0; i < _n; i++) {

        long double ax = 0;
        long double ay = 0;

        _computeAcceleration(&ax, &ay);

        _point.update(ax, ay, _dt);

        if (i % (_n / m) == 0) {
            points[pointIndex++] = _point;
        }
    }
}

void Arenstorf::_computeAcceleration(long double *ax, long double *ay)
{
    long double x = _point.getX();
    long double y = _point.getY();
    long double vx = _point.getVX();
    long double vy = _point.getVY();

    long double d1 = sqrtl((x + _alpha) * (x + _alpha) + y * y);
    long double D1 = d1 * d1 * d1;

    long double d2 = sqrtl((x - _beta) * (x - _beta) + y * y);
    long double D2 = d2 * d2 * d2;

    *ax = x + 2 * vy - _beta * (x + _alpha) / D1 - _alpha * (x - _beta) / D2;
    *ay = y - 2 * vx - _beta * y / D1 - _alpha * y / D2;
}

int Arenstorf::computeArenstorf(
        const ArenstorfPoint &init,
        unsigned int n,
        unsigned int m,
        long double dt,
        ostream &out) {

    Arenstorf arenstorf(init, n, dt);

    ArenstorfPoint* points = new ArenstorfPoint[m];

    arenstorf.computePoints(points, m);

    for (unsigned int i=0; i<m; i++)
    {
        out << points[i] << "\n";
    }

    return 0;
}