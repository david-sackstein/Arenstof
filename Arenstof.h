#pragma once

#include "ArenstofPoint.h"
#include <ostream>

class Arenstof
{
public:
	Arenstof(
			const ArenstofPoint &initialPoint,
			long double deltaT,
			int m,
			std::ostream &out);

	Arenstof(ArenstofPoint point, long double d, int i);

	void Update();


	static int computeArenstof(
			const ArenstofPoint &init,
			unsigned int n,
			unsigned int m,
			long double dt,
			std::ostream &out);

private:
	ArenstofPoint _point;
	long double _deltaT;
	int _m;
	std::ostream &_out;


};
