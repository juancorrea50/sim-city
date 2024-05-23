#ifndef RESCOLL_H
#define RESCOLL_H
#include <string>
#include <vector>
#include "residential.h"



class resColl{
    public:

    resColl();
    void resCollect(residential* rCell);
    //Sets the adjacent region around each residential cell
    void resAdj(vector<vector<cell*>> reg);

    //checks the region for powerlines and returns as true or false
    bool AdjPower(cell* res2);
    bool AdjRes(cell* res4);
    //checks the growth of each residential cell and increments the population based on conditions
    void resGrowth(int &workers);
    void resDecay(int &workers);
    void resGone(int &workers);
    //int howManyPoprNeighbors(residential* re);
    //residential* resConv(cell* re);
    //residential* poprSearch(residential* re);

    void printResVect();

    private:
    //create residential vector to store every residential cell
    vector<residential*> resVector;



};

#endif



//need to do:
//go through the whole region and collect the 'R' cells 
//R cells need a x, y position and population (set to 0 at first)
//Need a vector to store these R cells (vector can access the x, y, and pop of each R cell)
//Need to be able to check if there's a powerline in the adjacency of the R cell
/*
0 0 0
0 R 0
0 0 T
*/
//Will return a boolean value if there's a powerline
//Will need to check if it's adjacent to any other 'R's but will do later
//Will need to check the adjacency for other Rs and check their population
//Will need an if else block that iterates for every R in the vector
//Lastly, check the conditions for every 'R'











//Pop = 0, adj to 'P', inc pop
//Pop = 0, adj to 1 cell of pop 1, inc pop
//Pop = 1, adj to 2 cells of pop 1, inc pop
//Pop = 2, adj to 4 cells of pop 2, inc pop
//Pop = 3, adj to 6 cells of pop 3, inc pop
//Pop = 4, adj to 8 cells of pop 4, inc pop