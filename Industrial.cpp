#include "Industrial.h"

int Industrial::calcPowerConsumption()
{
	powerConsumption = 9 + (getPop() * 10); // TODO: find numbers that make sense. i dunno.
	return powerConsumption;
}

Industrial::Industrial(int x, int y)
{
	setX(x);
	setY(y);
}
