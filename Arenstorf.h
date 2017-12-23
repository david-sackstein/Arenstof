#pragma once

#include "ArenstorfPoint.h"
#include <ostream>

/**
 * Represents an arenstorf. Holds calculate methods which calculate the acceleration and location
 * of the ship at each time unit.
 */
class Arenstorf
{
public:

	/**
	 * Arenstorf constructor.
	 * @param init the first point of the ship .
	 * @param n number of times
	 * @param dt
	 */
	Arenstorf(
			const ArenstorfPoint &init,
			unsigned int n,
			long double dt);

	void computePoints(ArenstorfPoint *points, unsigned int m);

    static int computeArenstorf(
			const ArenstorfPoint &init,
			unsigned int n,
			unsigned int m,
			long double dt,
			std::ostream &out);

private:

	void _computeAcceleration(long double *ax, long double *ay);

	const long double _alpha = 0.012299;
	const long double _beta = 1 - _alpha;

	ArenstorfPoint _point;
	unsigned int _n;
	long double _dt;
};
