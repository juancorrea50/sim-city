#pragma once
#include <vector>
#include "cell.h"
class Industry
{
	struct direction {
		int dx;
		int dy;
	};
	
	public:
		const direction directions[8] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };

		vector<vector<cell*>> region; //A reference to the region in main

		vector<cell *> industrialCells; //storing the industrial cells.
		
		

		bool CheckIfAdjacentToType(char type, int x, int y);
		bool CheckIfAdjacentToPop(int minPop, int numNeighbours, int x, int y);
		int GetTotalAdjPop(int x, int y);

		Industry(const vector<vector<cell*>> &regionToAdd);
		void PrintAdjacentCells(int x, int y); //Debug function to print adjacent cells

		void CalculateIndustrialGrowth(int numCycles, int& workers, int& goods);
		void CalculateAllPollution();
		void CalculatePollutionOfOne(int x, int y);
		bool CheckIfCellCanGrow(int x, int y);

	private:
		int sizeX; // dimension of the region
		int sizeY; // dimension of the region
		vector<int> canGrow; //contains the indexes of industrialCells that can grow.
		vector<bool> industCellPowerAdj; //Same size & indexes as industrialCells, true if the cell is adj to a power source
		void CollectIndustrialCells(); //Stores the indsutrial cells from the region
		void SetCellCachedAdj(); //Does the initial check to see if a cell is adjacent to a power source, 
		//to avoid unneccessary future checks. (assuming the region layout doesn't ever change)
		int ResolveGrowth(); 
};

