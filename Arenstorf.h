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
	 * @param n number of times to calculate
	 * @param dt The difference in time which we want to calculate with
	 */
	Arenstorf(
			const ArenstorfPoint &init,
			unsigned int n,
			long double dt);

/**
 	* calculates the points that are given by calculating the acceleration
 	* @param points the points to calculate
 	* @param m number of times to calculate to points
 	*/
	void computePoints(ArenstorfPoint *points, unsigned int m);

	/**
	 * A static method which calculates the points by the acceleration, velocity and position and
	 * writes them to the output file.
	 * @param init the start point
	 * @param n num of steps
	 * @param m num of steps to save
	 * @param dt The difference in time which we want to calculate with
	 * @param out the outstream object, in this case ofstream
	 * @return -1 if there was an error, 0 if there was not.
	 */
	static int computeArenstorf(
			const ArenstorfPoint &init,
			unsigned int n,
			unsigned int m,
			long double dt,
			std::ostream &out);

private:

	/**
	 * calculate the acceleration by the current velocity and position, and the consts D1,D2.
	 * @param ax the start acceleration in x axis
	 * @param ay the start acceleration in y axis
	 */
	void _computeAcceleration(long double *ax, long double *ay);

	/**
	 * consts
	 */
	const long double _alpha = 0.012299;
	const long double _beta = 1 - _alpha;

	ArenstorfPoint _point;
	unsigned int _n;
	long double _dt;
};
