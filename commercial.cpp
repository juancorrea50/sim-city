#include "commercial.h"
#include <iostream>
#include <iterator>

//Constructor
commercial::commercial(){
    
}
commercial::commercial(int px, int py){
    setX(px);
    setY(py);
}
void commercial::setCellNeighbors(){
    for(int i = 0;i<getAdjVect().size();i++){
        for(int j = 0; j<getAdjVect()[i].size();j++){
            if(getAdjVect()[i][j]->getCellTag() == 'C'){
                if(getAdjVect()[i][j]->getX() != getX() || getAdjVect()[i][j]->getY() != getY()){
                    neighbors.push_back(getAdjVect()[i][j]);
                }
            }
        }
    }
}

//Print all cell information
void commercial::printInfo(){
    cout << getCellTag() << ": Commercial" << endl;
    cout << "X position: " << getX() << " | Y Position: " << getY() << endl;
    cout << "Population: " << getPop() << endl;
    cout << "Adjacency 2D Vector: " << endl;
    printAdjVect();
    cout << "Neighbors: " << endl;
    printCellNeighbors();
}
int commercial::calcPowerConsumption()
{
    powerConsumption = 2 + (getPop() * 4); // TODO: find numbers that make sense. i dunno.
    return powerConsumption;
}

void commercial::printCellNeighbors(){
    for(int i =0;i<neighbors.size();i++){
        cout << "Neighbor " << i+1 << ": X " << neighbors[i]->getX() << " Y " << neighbors[i]->getY() << endl;
    }
}


