#include <cmath>
#include <iostream>
#include "Arenstorf.h"

#define MEM_OUT "allocation failed"
#define INVALID_INPUT "The time must be non-negative"

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
 * @param dt The difference in time which we want to calculate with
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

/**
 * calculates the points that are given by calculating the acceleration
 * @param points the points to calculate
 * @param m number of times to calculate to points
 */
void Arenstorf::computePoints(ArenstorfPoint *points, unsigned int numSteps)
{

	unsigned int pointIndex = 0;
	unsigned int stepSize = _n / numSteps;

	for (unsigned int i = 0; i < _n; i++)
	{

		long double ax = 0;
		long double ay = 0;

		_computeAcceleration(&ax, &ay);

		_point.update(ax, ay, _dt);

		if (i % stepSize == 0)
		{
			points[pointIndex++] = _point;
		}
	}
}

/**
 * calculate the acceleration by the current velocity and position, and the consts D1,D2.
 * @param ax the start acceleration in x axis
 * @param ay the start acceleration in y axis
 */
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
int Arenstorf::computeArenstorf(
		const ArenstorfPoint &init,
		unsigned int n,
		unsigned int m,
		long double dt,
		std::ostream &out)
{

	if (n < m || dt < 0)
	{
		std::cerr << INVALID_INPUT << endl;
		return -1;
	}

	Arenstorf arenstorf(init, n, dt);

	// http://www.cplusplus.com/reference/new/nothrow/

	unsigned int numSteps = n / (n / m);
	ArenstorfPoint *points = new(std::nothrow) ArenstorfPoint[numSteps];
	if (points == nullptr)
	{
		std::cerr << MEM_OUT;
		return -1;
	}

	arenstorf.computePoints(points, numSteps);

	for (unsigned int i = 0; i < numSteps; i++)
	{
		out << points[i].getX() << "," << points[i].getY() << ",";
//		out << points[i];
	}

	out << "\n";
	delete[] points;
	return 0;
}