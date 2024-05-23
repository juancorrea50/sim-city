#pragma once
#include "cell.h"

class Powerplant : public cell
{
	public:
	Powerplant(int x, int y);
	//getters
	int getPowerProduction() {return powerProduction;}

	private:
	int powerProduction = 100;
};

