#pragma once

#include "ArenstofPoint.h"
#include <ostream>

class Arenstof
{
public:

    static int computeArenstof(
            const ArenstofPoint &init,
            unsigned int n,
            unsigned int m,
            long double dt,
            std::ostream &out);

	Arenstof(
			const ArenstofPoint &init,
			unsigned int n,
			unsigned int m,
			long double dt,
			std::ostream &out);

	void compute();

private:

	void computeAcceleration(long double *ax, long double *ay);
	void printIfNecessary(unsigned int index, unsigned int i) const;

	const long double alpha = 0.012299;
	const long double beta = 1 - alpha;

	ArenstofPoint _point;
	unsigned int _n;
	unsigned int _m;
	long double _dt;
	std::ostream &_out;
};
