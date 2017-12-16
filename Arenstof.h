#pragma once

#include "ArenstofPoint.h"
#include <ostream>

class Arenstof
{
public:

	Arenstof(
			const ArenstofPoint &init,
			unsigned int n,
			long double dt);

	void computePoints(ArenstofPoint *points, unsigned int m);

    static int computeArenstof(
            const ArenstofPoint &init,
            unsigned int n,
            unsigned int m,
            long double dt,
            std::ostream &out);

private:

	void computeAcceleration(long double *ax, long double *ay);

	const long double alpha = 0.012299;
	const long double beta = 1 - alpha;

	ArenstofPoint _point;
	unsigned int _n;
	long double _dt;
};
