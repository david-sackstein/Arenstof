#include <cmath>
#include "Arenstof.h"

Arenstof::Arenstof(
    const ArenstofPoint &initialPoint,
    unsigned int n,
    unsigned int m,
    long double dt,
    std::ostream &out)
    :
    _point(initialPoint),
    _n(n),
    _m(m),
    _dt(dt),
    _out(out)
{
}

long double expectedResults[] = {
    9.940e-01, -3.416e+00,
    -9.133e+02, -6.831e+00,
    -1.836e+03, 3.101e+03,
    5.186e+03, 9.339e+03,
    2.815e+04, 6.373e+02,
    3.652e+04, -5.925e+04,
    -7.752e+04, -1.459e+05,
    -3.808e+05, -1.577e+04,
    -4.658e+05, 7.246e+05,
    8.672e+05, 1.709e+06};

void Arenstof::compute() {

    unsigned int index = 0;
    for (unsigned int i = 0; i < _n; i++, index++) {

        long double ax = 0;
        long double ay = 0;

        computeAcceleration(&ax, &ay);

        _point.Update(ax, ay, _dt);

        printIfNecessary(index, i);
    }
}

void Arenstof::printIfNecessary(unsigned int index, unsigned int i) const {
    if (i % (_n / _m) == 0) {
        ArenstofPoint expected (
            expectedResults[2 * index],
            expectedResults[2 * index + 1],
            0, 0);

        _out << "Actual   = " << _point << "\n";
        _out << "Expected = " << expected << "\n";
    }
}

void Arenstof::computeAcceleration(long double *ax, long double *ay)
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

int Arenstof::computeArenstof(
        const ArenstofPoint &init,
        unsigned int n,
        unsigned int m,
        long double dt,
        std::ostream &out) {

    Arenstof arenstof(init, n, m, dt, out);
    arenstof.compute();

    return 0;
}