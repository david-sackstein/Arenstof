#include <cmath>
#include "Arenstorf.h"

using namespace std;

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

        computeAcceleration(&ax, &ay);

        _point.Update(ax, ay, _dt);

        if (i % (_n / m) == 0) {
            points[pointIndex++] = _point;
        }
    }
}

void Arenstorf::computeAcceleration(long double *ax, long double *ay)
{
    long double x = _point.getX();
    long double y = _point.getY();
    long double vx = _point.getVX();
    long double vy = _point.getVY();

    long double D1 = powl(((x + alpha) * (x + alpha) + y * y), 3.0 / 2.0);
    long double D2 = powl(((x - beta) * (x - beta) + y * y), 3.0 / 2.0);

    *ax = x + 2 * vy - beta * (x + alpha) / D1 - alpha * (x - beta) / D2;
    *ay = y - 2 * vx - beta * y / D1 - alpha * y / D2;
}

int Arenstorf::computeArenstof(
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