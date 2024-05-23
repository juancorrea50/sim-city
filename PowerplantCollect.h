#pragma once
#include "Powerplant.h"

class PowerplantCollect
{

	public:
		vector<vector<cell*>> region; //A reference to the region in main
		vector<Powerplant*> powerplants; // collection of all power plants
		vector<cell*> validEmptyCells; //Empty cells that are suitable for a new power plant

		void SetRegion(vector<vector<cell*>> &mainRegion);
		void CalcPower(int &powerProd, int &powerCons, int &workers);

		int CalculateInitialPowerUse(); //Calculates the power consumption of the entire region.
		int GetTotalPower();
		void CollectEmptyCells();
		void CollectPowerplantCell(Powerplant* p);

	private:
		void PlaceNewPowerplant();
		int totalPower = 0;
		bool emptyCellsCollected = false;
};

