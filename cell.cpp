#include "cell.h"
#include <iostream>

using namespace std;

cell::cell(){
    posX = -1;
    posY = -1;
    pop = 0;
    pollution = 0;
}
cell::cell(int x, int y){
    posX = x;
    posY = y;
    pop = 0;
    pollution = 0;
}
void cell::setX(int x){
    posX = x;
}
void cell::setY(int y){
    posY = y;
}
void cell::incPop(){
    pop++;
    calcPowerConsumption();
}

void cell::decPop()
{
    pop--;
}

int cell::calcPowerConsumption()
{
    powerConsumption = pop; //just if a child class of cell forgot to override this func.
    return powerConsumption;
}

void cell::setTag(char c){
    cellTag = c;
}
void cell::setPollution(int poll)
{
    pollution = poll;
}
void cell::setVisited(bool v){
    visited = v;
}
void cell::setPop(int p){
    pop = p;
}
int cell::addPopulations(){
    int i,j;
    int total = 0;
    for(i=0;i<adjVect.size();i++){
        for(j=0;j<adjVect[i].size();j++){
            total += adjVect[i][j]->getPop();
        }
    }
    return total;
}
void cell::setAdjVect(vector<vector<cell*>> region){
    //Append all neighbors to adjVect
        if(posX == 0 && posY == 0){
            //Top left corner case
            //Middle Row
            adjVect.push_back({region[posX][posY],region[posX][posY+1]});
            //Bottom Row
            adjVect.push_back({region[posX+1][posY],region[posX+1][posY+1]});
        } else if(posX == 0 && posY >= region[0].size() - 1){
            //Top right corner case
            //Middle Row
            adjVect.push_back({region[posX][posY-1],region[posX][posY]});
            //Bottom Row
            adjVect.push_back({region[posX+1][posY-1],region[posX+1][posY]});
        } else if(posX >= region.size() - 1 && posY == 0){
            //Bottom left corner case
            //Top row
            adjVect.push_back({region[posX-1][posY],region[posX-1][posY+1]});
            //Middle Row
            adjVect.push_back({region[posX][posY],region[posX][posY+1]});
        } else if(posX >= region.size() - 1 && posY >= region[0].size() - 1){
            //Bottom right corner case
            //Top row
            adjVect.push_back({region[posX-1][posY-1],region[posX-1][posY]});
            //Middle Row
            adjVect.push_back({region[posX][posY-1],region[posX][posY]});
        } else if(posX >= region.size() - 1){
            //Bottom Edge case scenario
            //Top row
            adjVect.push_back({region[posX-1][posY-1],region[posX-1][posY], region[posX-1][posY+1]});
            //Middle Row
            adjVect.push_back({region[posX][posY-1],region[posX][posY],region[posX][posY+1]});
        } else if(posX == 0){
            //Top edge case scenario
            //Middle Row
            adjVect.push_back({region[posX][posY-1],region[posX][posY],region[posX][posY+1]});
            //Bottom Row
            adjVect.push_back({region[posX+1][posY-1],region[posX+1][posY],region[posX+1][posY+1]});
        } else if(posY == 0){
            //Far left edge case scenario
            //Top row
            adjVect.push_back({region[posX-1][posY], region[posX-1][posY+1]});
            //Middle Row
            adjVect.push_back({region[posX][posY],region[posX][posY+1]});
            //Bottom Row
            adjVect.push_back({region[posX+1][posY],region[posX+1][posY+1]});
        } else if(posY >= region[0].size() - 1){
            //Far right edge case scenario
            //Top row
            adjVect.push_back({region[posX-1][posY-1],region[posX-1][posY]});
            //Middle Row
            adjVect.push_back({region[posX][posY-1],region[posX][posY]});
            //Bottom Row
            adjVect.push_back({region[posX+1][posY-1],region[posX+1][posY]});
        } 
        else {
            //Top row
            adjVect.push_back({region[posX-1][posY-1],region[posX-1][posY], region[posX-1][posY+1]});
            //Middle Row
            adjVect.push_back({region[posX][posY-1],region[posX][posY],region[posX][posY+1]});
            //Bottom Row
            adjVect.push_back({region[posX+1][posY-1],region[posX+1][posY],region[posX+1][posY+1]});
        }
}


//Prints neighbor array
void cell::printAdjVect(){
    for (int i = 0; i < adjVect.size(); i++) {
            for (int j = 0; j < adjVect[i].size(); j++) {
                cout << adjVect[i][j]->getCellTag() << " ";
            }
        cout << endl;
    }
}
