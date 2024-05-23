#include "residential.h"
#include <iostream>
#include <iterator>

residential::residential(int rx, int ry) 
{
        setX(rx);
        setY(ry);
}

void residential::printResNeighbors()
{
    for(int i =0;i<resNeighbors.size();i++){
        cout << "Neighbor " << i+1 << ": X " << resNeighbors[i]->getX() << " Y " << resNeighbors[i]->getY() << endl;
    }
}
//Sets the residential vector for the residential neighbors
void residential::setResNeighbors()
{
    for(int i = 0;i<getAdjVect().size();i++){
        for(int j = 0; j<getAdjVect()[i].size();j++){
            if(getAdjVect()[i][j]->getCellTag() == 'R'){
                if(getAdjVect()[i][j]->getX() != getX() || getAdjVect()[i][j]->getY() != getY()){
                    resNeighbors.push_back(getAdjVect()[i][j]);
                }
            }
        }
    }
}

int residential::calcPowerConsumption()
{
    powerConsumption = (getPop() * 1); // TODO: find numbers that make sense. i dunno.
    return powerConsumption;
}

//output values for each residential cell
void residential::printRes() {
    cout << getCellTag() << ": Residential" << endl;
    cout << "X position: " << getX() << " | Y Position: " << getY() << endl;
    cout << "Population: " << getPop() << endl;
    cout << "Adjacency 2D Vector: " << endl;
    printAdjVect();

    
}
