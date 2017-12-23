#pragma once

#include "ArenstorfPoint.h"
#include <ostream>

class Arenstorf
{
public:

	Arenstorf(
			const ArenstorfPoint &init,
			unsigned int n,
			long double dt);

	void computePoints(ArenstorfPoint *points, unsigned int m);

    static int computeArenstof(
            const ArenstorfPoint &init,
            unsigned int n,
            unsigned int m,
            long double dt,
            std::ostream &out);

private:

	void computeAcceleration(long double *ax, long double *ay);

	const long double alpha = 0.012299;
	const long double beta = 1 - alpha;

	ArenstorfPoint _point;
	unsigned int _n;
	long double _dt;
};
