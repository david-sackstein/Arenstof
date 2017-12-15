#pragma once

#include "ArenstofPoint.h"
#include <ostream>

class Arenstof
{
    static int computeArenstof(
        const ArenstofPoint& init,
        unsigned int n,
        unsigned int m,
        long double dt,
        std::ostream& out);
};
