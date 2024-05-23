#ifndef COMMERCIAL_H
#define COMMERCIAL_H
#include <string>
#include <vector>
#include "cell.h"

using namespace std;

class commercial: public cell{
    public:
    commercial();
    commercial(int px, int py);
    void printCellNeighbors();
    void setCellNeighbors();
    void printInfo();
    int calcPowerConsumption();
    vector<cell*> getCellNeighbors(){return neighbors;}
    private:
    vector<cell*> neighbors;

};

#endif