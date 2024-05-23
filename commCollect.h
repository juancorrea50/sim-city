#ifndef COMMCOLLECT_H
#define COMMCOLLECT_H
#include <string>
#include <vector>
#include "commercial.h"
#include "SportsArena.h"

using namespace std;

class commCollect{
    public:
    //Constructor
    commCollect();
    void collectCells(commercial* cCell);

    //Setters
    void setAllAdj(vector<vector<cell*>> r);
    void setHasArena(bool a);
    //Commercial Logic Functions
    void commercialGrowth(int &avWorkers, int &avGoods, vector<vector<cell*>> &region);
    bool isPowerAdj(cell* chosen);
    int howManyPopNeighbors(commercial* c);
    commercial* cellConv(cell* c);
    commercial* popSearch(commercial* c);
    //Arena Functionality
    void arenaCheck(vector<vector<cell*>> &r);
    void createArena(vector<vector<cell*>> &region);
    void startEvent(vector<vector<cell*>> &r);
    void endEvent();
    //Getters
    bool getHasArena(){return hasArena;}



    void cleanUp();
    void printVector();
    private:
    vector<commercial*> commVector;
    bool hasArena;
    SportsArena* Arena;



};

#endif