#include "Arenstof.h"

Arenstof::Arenstof(
    const ArenstofPoint& initialPoint,
    long double deltaT,
    int m,
    std::ostream& out)
:
    _point(initialPoint),
    _deltaT(deltaT),
    _m(m),
    _out(out)
{
}

void Arenstof::Update()
{
    // calculate the next step and write to the output if required
}

int Arenstof::computeArenstof(
    const ArenstofPoint& init,
    unsigned int n,
    unsigned int m,
    long double dt,
    std::ostream& out)
{
    return 0;
}