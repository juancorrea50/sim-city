#include "PowerplantCollect.h"
#include <iostream>

void PowerplantCollect::SetRegion(vector<vector<cell*>> &mainRegion)
{
	region = mainRegion;
}

void PowerplantCollect::CalcPower(int& powerProd, int& powerCons, int& workers)
{
	if (!emptyCellsCollected)
		CollectEmptyCells();
	powerCons = CalculateInitialPowerUse();


	if (powerProd <= powerCons)
	{
		PlaceNewPowerplant();
		powerProd += 100;
	}
}

int PowerplantCollect::CalculateInitialPowerUse()
{
	//go through each cell in the region and get the power
	//ineffecient but easy. im lazy
	//probably better to increment power consumption whenever a r/c/i cell grows. 
	int total = 0;

	for (int i = 0; i < region.size(); i++)
	{
		for (int j = 0; j < region[i].size(); j++)
		{
			total += region[i][j]->calcPowerConsumption();
		}
	}

	return total;
}

int PowerplantCollect::GetTotalPower()
{
	int total = 0;

	for (int i = 0; i < powerplants.size(); i++)
	{
		total += powerplants[i]->getPowerProduction();
	}

	return total;
}

void PowerplantCollect::CollectEmptyCells()
{
	vector<cell*> allEmptyCells;
	allEmptyCells.resize(0);
	validEmptyCells.resize(0);
	for (int i = 0; i < region.size(); i++)
	{
		for (int j = 0; j < region[i].size(); j++)
		{
			if (region[i][j]->getCellTag() == ' ')
			{
				allEmptyCells.push_back(region[i][j]);
			}
		}
	}

	//find suitable place for new powerplant
	//suitable = not close to a residential cell
	int range = 3;

	//TODO: would be more effecient to work backwards from the residential cells. oh well.
	for (int i = 0; i < allEmptyCells.size(); i++)
	{
		int ix = allEmptyCells[i]->getX();
		int iy = allEmptyCells[i]->getY();

		bool valid = true; //Becomes false if empty cell is within range of a residential cell.


		//check if in range of a cell that makes it an invalid spot. (residential)
		for (int x = allEmptyCells[i]->getX() - range;
			x <= allEmptyCells[i]->getX() + range; x++)
		{
			for (int y = allEmptyCells[i]->getY() - range;
				y <= allEmptyCells[i]->getY() + range; y++)
			{
				if (x >= 0 && x < region.size()
					&& y >= 0 && y < region[0].size() && valid)
				{
					//if cell is residential, remove from validemptycells.
					if (region[x][y]->getCellTag() == 'R')
					{
						valid = false;
						break;
					}
				}
				
			}
		}

		if (valid)
			validEmptyCells.push_back(allEmptyCells[i]);

		//cout << endl << allEmptyCells.size() << " " << validEmptyCells.size() << endl;
	}

	emptyCellsCollected = true;
}

void PowerplantCollect::CollectPowerplantCell(Powerplant* p)
{
	powerplants.push_back(p);
}

void PowerplantCollect::PlaceNewPowerplant()
{
	//choose a cell from validEmptyCells to place a new powerplant
	srand(time(0)); // set seed for random number generator
	int r = rand() % (validEmptyCells.size() - 1); //random index for valid empty cells
	int px = validEmptyCells[r]->getX();
	int py = validEmptyCells[r]->getY(); 


	int ring = 1;

	int nx; //nearest powered cell coord
	int ny;

	//connect newly placed powerplant to nearest powered cell with powerlines
		//find neearest powered cell
			//I , R, C , T , #
			//this is where id want a region class so i could easily get all the residential, industrial, etc cells from it. dont feel like refactoring everything for this though.
			//just gonna search in rings around the chosen cell until it matches a powered cell.
	bool found = false;
	vector<int> validx;
	vector<int> validy;
	int loops = 0;

	while (!found || loops < 10000) //lazy way of avoiding infinite loop
	{
		for (int x = px - ring; x <= px + ring; x++)
		{
			for (int y = py - ring; y <= py + ring; y++)
			{
				if (x >= 0 && x < region.size()
					&& y >= 0 && y < region[0].size())
				{
					if (region[x][y]->getCellTag() == 'R' || region[x][y]->getCellTag() == 'I' 
					|| region[x][y]->getCellTag() == 'T' || region[x][y]->getCellTag() == '#'
					|| region[x][y]->getCellTag() == 'C')
					{
						found = true;
						nx = x;
						ny = y;
						validx.push_back(nx);
						validy.push_back(ny);
						loops++;
					}
				}
			}
		}
		if (!found) ring++;
	}

	//if multiple found cells were found on the same ring, we want the shortest distance one
	int bestIndex = 0;
	int bestDist = 10000000;
	for (int i = 0; i < validx.size(); i++)
	{
		int d = (abs(validx[i] - px)) + (abs(validy[i] - py));
		if (d < bestDist)
		{
			bestIndex = i;
			bestDist = d;
		}
	}

	nx = validx[bestIndex];
	ny = validy[bestIndex];
	
	region[px][py]->setTag('P');

	//find a 'short' path of empty cells
	//p is the coord of the powerplant, n is the coord of the found power source

	int sx = (px <= nx) ? px : nx; //sx is the smaller x coord value
	int lx = (px <= nx) ? nx : px; //lx is the larger x coord value

	int sy = (py <= ny) ? py : ny;
	int ly = (py <= ny) ? ny : py;

	int iterx = sx;

	//cout << "\n sx: " << sx << ", lx: " << lx << ", sy: " << sy << ", ly: " << ly << endl;

	for (int ix = sx; ix < lx; ix++)
	{
		if (region[ix][py]->getCellTag() != 'P')
		{
			if (region[ix][py]->getCellTag() == '-')
				region[ix][py]->setTag('#');
			else region[ix][py]->setTag('T');
		}
		iterx = ix;
	}

	for (int iy = sy; iy < ly; iy++)
	{
		if (region[iterx][iy]->getCellTag() != 'P')
		{
			if (region[iterx][iy]->getCellTag() == '-')
				region[iterx][iy]->setTag('#');
			else region[iterx][iy]->setTag('T');
		}
	}
}

