#include <iostream>
#include "ArenstorfPoint.h"

/**
 * This class represents an ArenstorfPoint. It holds the attributes x,y,vx,vy, which represent
 * the velocity and point of the ship at each time unit.
 */


/**
* A default constructor, initializes the attributes with 0.
*/
ArenstorfPoint::ArenstorfPoint() :
		_x(0),
		_y(0),
		_vx(0),
		_vy(0)
{
}

/**
 * ArenstorfPoint constructor which receives x,y,vx,vy.
 * @param x the position in x axis
 * @param y the position in y axis
 * @param vx the velocity in x axis
 * @param vy the velocity in y axis
 */
ArenstorfPoint::ArenstorfPoint(
		long double x,
		long double y,
		long double vx,
		long double vy)
		:
		_x(x),
		_y(y),
		_vx(vx),
		_vy(vy)
{
}

/**
 * Updates x,y,vx,vy using dt and the acceleration (ax,ay)
 * @param ax acceleration in the x axis
 * @param ay acceleration in the y axis
 * @param dt the time unit
 */
void ArenstorfPoint::update(long double ax, long double ay, long double dt)
{
	_x = _x + _vx * dt;
	_y = _y + _vy * dt;
	_vx = _vx + ax * dt;
	_vy = _vy + ay * dt;
}

/**
 * friend method - print the point.
 * @param os
 * @param p point to print
 * @return ostream object.
 */
std::ostream &operator<<(std::ostream &os, const ArenstorfPoint &p)
{
	//os << "(" << p._x << ", " << p._y << ")";
	std::cout.precision(5);
	os << p._x << ", " << p._y;
	return os;
}

