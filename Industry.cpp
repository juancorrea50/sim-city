#include "Industry.h"
#include <iostream>

/// <summary>
/// Checks if a cell is adjacent to a cell of celltype
/// </summary>
/// <param name="type">The type of cell to check for</param>
/// <param name="x">The x coordinate of the cell</param>
/// <param name="y">The y coordinate of the cell</param>
/// <returns>Returns true if there exists an adjacent cell of celltype</returns>
bool Industry::CheckIfAdjacentToType(char c, int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		if (x + directions[i].dx >= 0 && x + directions[i].dx < sizeX - 1 &&
			y + directions[i].dy >= 0 && y + directions[i].dy < sizeY - 1)
		{
			if (region[x + directions[i].dx][y + directions[i].dy]->getCellTag() == c)
			{
				return true;
			}
		}
	}
	return false;
}

/// <summary>
/// Checks if a cell has a surrounding cell with a population of atleast minPop
/// </summary>
/// <param name="minPop">the population required for this to return true</param>
/// <param name="numNeighbours">the number of neighbours who have a population of atleast minPop for this function to return true</param>
/// <param name="x">x coord of cell</param>
/// <param name="y">y coord of cell</param>
/// <returns>returns true if</returns>
bool Industry::CheckIfAdjacentToPop(int minPop, int numNeighbours, int x, int y)
{
	int found = 0;
	for (int i = 0; i < 8; i++)
	{
		if (x + directions[i].dx >= 0 && x + directions[i].dx < sizeX - 1 &&
			y + directions[i].dy >= 0 && y + directions[i].dy < sizeY - 1)
		{
			//cout << "adj pop is " << region[x + directions[i].dx][y + directions[i].dy].GetPopulation() << ", ";
			if (region[x + directions[i].dx][y + directions[i].dy]->getPop() >= minPop)
			{
				found++;
			}
		}
	}
	return found >= numNeighbours;
}

int Industry::GetTotalAdjPop(int x, int y)
{
	int pop = 0;
	for (int i = 0; i < 8; i++)
	{
		if (x + directions[i].dx >= 0 && x + directions[i].dx < sizeX - 1 &&
			y + directions[i].dy >= 0 && y + directions[i].dy < sizeY - 1)
		{
			pop += region[x + directions[i].dx][y + directions[i].dy]->getPop();
		}
	}
	return pop;
}

Industry::Industry(const vector<vector<cell *>> &regionToAdd)
{
	region = regionToAdd;
	sizeX = region.size();
	sizeY = region.at(0).size(); //assumes region is rectangular.
}

/// <summary>
/// Debug function to output the cells adjacent to a given cell's coordinate.
/// </summary>
/// <param name="x">x coordinate of the cell</param>
/// <param name="y">y coordinate of the cell</param>
void Industry::PrintAdjacentCells(int x, int y)
{
	cout << endl << "Cells adjacent to " << region[x][y]->getCellTag() << " (" << x << ", " << y << ") " << endl;
	for (int i = 0; i < 8; i++)
	{
		if (x + directions[i].dx >= 0 && x + directions[i].dx < sizeX - 1 &&
			y + directions[i].dy >= 0 && y + directions[i].dy < sizeY - 1)
		{
			if (i == 3 || i == 5)
				cout << endl;
			if (i == 4)
				cout << " ";
			cout << region[x + directions[i].dx][y + directions[i].dy]->getCellTag();
		}
	}
	cout << endl;
}

/// <summary>
/// Iterates through the region and adds the industrial type cells to the vector "industrialCells"
/// </summary>
/// <param name="region">The region to read</param>
void Industry::CollectIndustrialCells()
{
	for (int i = 0; i < region.size(); i++)
	{
		for (int j = 0; j < region[i].size(); j++)
		{
			if (region[i][j]->getCellTag() == 'I')
				industrialCells.push_back(region[i][j]);
		}
	}

	SetCellCachedAdj();
}

/// <summary>
/// //Does the initial check to see if a cell is adjacent to a power source, 
/// to avoid unneccessary future checks. (assuming the region layout doesn't ever change).
/// Requires CollectIndustrialCells to have been called.
/// </summary>
void Industry::SetCellCachedAdj()
{
	industCellPowerAdj.resize(industrialCells.size());

	for (size_t i = 0; i < industrialCells.size(); i++)
	{
		industCellPowerAdj[i] = false;
	}

	if (industrialCells.size() > 0)
	{
		for (int i = 0; i < industrialCells.size(); i++)
		{
			if (CheckIfAdjacentToType('P', industrialCells.at(i)->getX(), industrialCells.at(i)->getY()))
				industCellPowerAdj[i] = true;
			else if (CheckIfAdjacentToType('T', industrialCells.at(i)->getX(), industrialCells.at(i)->getY()))
				industCellPowerAdj[i] = true;
			else if (CheckIfAdjacentToType('#', industrialCells.at(i)->getX(), industrialCells.at(i)->getY()))
				industCellPowerAdj[i] = true;
		}
	}
}

//I completely forgot about this part of the growth requirements until the night before it was due
//So this is fisher-price code - Trey
int Industry::ResolveGrowth()
{
	vector<int> finals;
	bool tie = true;
	int highest = 0;
	int index = 0; //index of highest pop cell
	//Find prioritized cell. Higher population wins. If tie, higher adj total pop wins.
	for (int i = 0; i < canGrow.size(); i++)
	{
		if (industrialCells[canGrow[i]]->getPop() == highest)
		{
			tie = true;
		}
		else if (industrialCells[canGrow[i]]->getPop() > highest && industrialCells[i]->getPop() < 3)
		{
			tie = false;
			index = i;
			highest = industrialCells[canGrow[i]]->getPop();
		}
	}
	if (tie)
	{ //find which cell has the highest adj pop total
		int highestAdj = 0;
		bool stillTie = true;
		int newIndex = -1;
		int lowestCoordIndex = -1;
		for (int i = 0; i < canGrow.size(); i++)
		{
			if(industrialCells[canGrow[i]]->getPop() == highest)
			{
				if(newIndex == -1)
				{
					lowestCoordIndex = i;
				}
				int pop = GetTotalAdjPop(industrialCells[canGrow[i]]->getX(),
				 industrialCells[canGrow[i]]->getY());
				if (pop == highestAdj)
				{
					stillTie = true;
					finals.push_back(canGrow[i]);
				}
				else if (pop > highestAdj)
				{
					stillTie = false;
					highestAdj = pop;
					newIndex = i;
				}
			}
		}
		if(stillTie)
		{
			int final = 0;
			int lx = -1;
			int ly = -1;
			for (size_t i = 0; i < finals.size(); i++)
			{
				if (ly == -1)
				{
					ly = industrialCells[finals[i]]->getY();
					lx = industrialCells[finals[i]]->getX();
					final = i;
				}
				else if (industrialCells[finals[i]]->getY() < ly)
				{
					ly = industrialCells[finals[i]]->getY();
					lx = industrialCells[finals[i]]->getX();
					final = i;
				}
				else if (industrialCells[finals[i]]->getY() == ly)
				{
					//this code is repetitive because it is 1am right now
					if (industrialCells[finals[i]]->getX() < lx)
						final = i;
				}
			}
			return final;
		}
		else
		{
			return newIndex;
		}
	}
	else
	{
		return index;
	}
}

//conditions for growth.
// if pop = 0, must be adj to a powerline & 2 available workers.
//			OR:	adj to a cell with atleast 1 pop & 2 available workers.
//if pop = 1, adj to two cells with 1 pop & 2 available workers
//if pop = 2, adj to four cells with 2 pop & 2 available workers.

/// <summary>
/// Calculates the growth for all industrial cells
/// </summary>
/// <param name="region">The number of time cycles to run</param>
void Industry::CalculateIndustrialGrowth(int numCycles, int& workers, int& goods)
{
	//Make sure the collection of industrial cells has been made
	if (industrialCells.size() <= 0)
	{
		CollectIndustrialCells();
	}

	for (int c = 0; c < numCycles; c++)
	{
		if (workers >= 2)
		{
			for (int i = 0; i < industrialCells.size(); i++)
			{
				if (industrialCells.at(i)->getPop() == 0)
				{
					if (industCellPowerAdj[i] && workers >= 2)
					{
						canGrow.push_back(i);
					}
					else if (CheckIfAdjacentToPop(1, 1, industrialCells.at(i)->getX(), industrialCells.at(i)->getY())
						&& workers >= 2)
					{
						canGrow.push_back(i);
					}
				}
				else if (industrialCells.at(i)->getPop() == 1)
				{
					if (CheckIfAdjacentToPop(1, 2, industrialCells.at(i)->getX(), industrialCells.at(i)->getY())
						&& workers >= 2)
					{
						canGrow.push_back(i);
					}
				}
				else if (industrialCells.at(i)->getPop() == 2)
				{
					if (CheckIfAdjacentToPop(2, 4, industrialCells.at(i)->getX(), industrialCells.at(i)->getY())
						&& workers >= 2)
					{
						canGrow.push_back(i);
					}
				}
			}
		}
		if(canGrow.size() > 0)
		{
			if (canGrow.size() > 1)
			{
				int ind = ResolveGrowth();
				//region[industrialCells[canGrow[ind]]->getX()][industrialCells[canGrow[ind]]->getY()]->incPop();
				industrialCells[canGrow[ind]]->incPop();
				goods++;
				workers--;
			}
			else
			{
				//region[industrialCells[canGrow[0]]->getX()][industrialCells[canGrow[0]]->getY()]->incPop();
				industrialCells[canGrow[0]]->incPop();
				goods++;
				workers--;
			}
		}
		canGrow.clear();
		/*for (size_t i = 0; i < industrialCells.size(); i++)
		{
			cout << industrialCells[i]->getPop();
		}
		cout << endl;*/
		}
}

//Calculates the pollution for all cells
//TODO: This is inneffecient. I don't need to update the pollution until we need to display it
//If we're just displaying one cell's pollution, we only need to update the pollution for that single cell.
//But right now every cell is getting their pollution updated every cycle.

/// <summary>
/// Calculates the pollution of all cells
/// </summary>
void Industry::CalculateAllPollution()
{
	//for updating the entire region's pollution
	//go through every industrial cell
	for (int i = 0; i < industrialCells.size(); i++)
	{
		int rings = industrialCells[i]->getPop() - 1;
		if (rings >= 1)
		{
			for (int x = industrialCells[i]->getX() - rings;
				x <= industrialCells[i]->getX() + rings; x++)
			{
				for (int y = industrialCells[i]->getY() - rings;
					y <= industrialCells[i]->getY() + rings; y++)
				{
					if (x == industrialCells[i]->getX() &&
						y == industrialCells[i]->getY())
					{
						//dont need to update pollution of own cell.
						region[x][y]->setPollution(region[x][y]->getPop());
					}
					else
					{
						if (x >= 0 && x < region.size()
							&& y >= 0 && y < region[0].size())
						{
							int ix = industrialCells[i]->getX();
							int iy = industrialCells[i]->getY();
							int px = (rings+1) - abs(ix-x);
							int py = (rings+1) - abs(iy-y);
							int p = px < py ? px : py;
							if (region[x][y]->getCellTag() == 'I')
							{
								region[x][y]->setPollution(region[x][y]->getPop() + p);
							}
							else{
								region[x][y]->setPollution(region[x][y]->getPollution() + p);
							}
							
						}
					}
				}
			}
		}
	}
	/*for (size_t i = 0; i < region.size(); i++)
	{
		cout << endl;
		for (size_t j = 0; j < region[i].size(); j++)
		{
			cout << region[i][j]->getPollution();
		}
	}*/
	
}

/// <summary>
/// Calculates the pollution of a single cell
/// </summary>
/// <param name="x">The x coord of the cell</param>
/// <param name="y">The y coord of the cell</param>
void Industry::CalculatePollutionOfOne(int x, int y)
{
	//for updating a single cell's pollution
	//go through each cell in the region, and check if it's in range of every indsutrial cell
	//range = pollution. if it's in range, increment pollutionToAdd.
	for (int x = 0; x < region.size(); x++)
	{
		for (int y = 0; y < region[x].size(); y++)
		{
			int pollutionToAdd = 0;
			for (int i = 0; i < industrialCells.size(); i++)
			{
				if (abs(x - industrialCells.at(i)->getX()) < industrialCells.at(i)->getPop()
				|| abs(y - industrialCells.at(i)->getY()) < industrialCells.at(i)->getPop())
				{
					int ix = industrialCells[i]->getX();
					int iy = industrialCells[i]->getY();
					int bp = industrialCells[i]->getPop() - 1;
					int px = abs(ix - x);
					int py = abs(iy - y);
					int p = px < py ? bp - px: bp - py;
					if(p>0)
						pollutionToAdd+= p;
				}
			}
			region[x][y]->setPollution(pollutionToAdd);
		}
	}
}

//Checks if a cell at the given coordinates has the ability to grow
//Assumes the checks for available workers has already been done
bool Industry::CheckIfCellCanGrow(int x, int y)
{
	if(region[x][y]->getPop() == 0)
	{
		if (CheckIfAdjacentToType('P', x, y))
			return true;
		else if (CheckIfAdjacentToType('T', x, y))
			return true;
		else if (CheckIfAdjacentToType('#', x, y))
			return true;
		else if (CheckIfAdjacentToPop(1,1,x,y))
			return true;
	}
	else if(region[x][y]->getPop() == 1)
	{
		if (CheckIfAdjacentToPop(1,2,x,y))
			return true;
	} 
	else if(region[x][y]->getPop() == 2)
	{
		if(CheckIfAdjacentToPop(2,4,x,y))
			return true;
	}
	return false;
}
