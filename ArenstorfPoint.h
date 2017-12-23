#pragma once

#include <ostream>

/**
 * This class represents an ArenstorfPoint. It holds the attributes x,y,vx,vy, which represent
 * the velocity and point of the ship at each time unit.
 */
class ArenstorfPoint
{
public:

/**
 * A default constructor, initializes the attributes with 0.
 */
	ArenstorfPoint();

/**
 * ArenstorfPoint constructor which receives x,y,vx,vy.
 * @param x the position in x axis
 * @param y the position in y axis
 * @param vx the velocity in x axis
 * @param vy the velocity in y axis
 */
	ArenstorfPoint(
			long double x,
			long double y,
			long double vx,
			long double vy);

	/**
	 * inline method - get x.
	 * @return x
	 */
	long double getX() const
	{ return _x; }

	/**
	 * inline method - get y.
	 * @return y
	 */
	long double getY() const
	{ return _y; }

	/**
	 * inline method - get vx.
	 * @return vx
	 */
	long double getVX() const
	{ return _vx; }

	/**
	 * inline method - get vy.
	 * @return vy
	 */
	long double getVY() const
	{ return _vy; }

	/**
	 * friend method - print the point.
	 * @param os
	 * @param p point to print
	 * @return osream object.
	 */
	friend std::ostream &operator<<(std::ostream &os, const ArenstorfPoint &p);

/**
 * Updates x,y,vx,vy using dt and the acceleration (ax,ay)
 * @param ax acceleration in the x axis
 * @param ay acceleration in the y axis
 * @param dt the time unit
 */
	void update(long double ax, long double ay, long double dt);

private:

	/**
	 * represent the location and velocity of the ship in every time unit
	 */
	long double _x;
	long double _y;
	long double _vx;
	long double _vy;
};
