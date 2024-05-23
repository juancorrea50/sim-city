#ifndef CELL_H
#define CELL_H
#include <string>
#include <vector>

using namespace std;

class cell{
    public:
    //Constructors
    cell();
    cell(int x, int y);
    //Mod AdjVect
    void setAdjVect(vector<vector<cell*>> region);
    void printAdjVect();
    int addPopulations();
    //Setters
    void setX(int x);
    void setY(int y);
    void setTag(char c);
    void setPollution(int poll);
    void setVisited(bool v);
    void setPop(int p);

    //Getters
    int getPop(){return pop;}
    int getPollution() { return pollution; }
    int getX(){return posX;}
    int getY(){return posY;}
    char getCellTag(){return cellTag;}
    bool getVisited(){return visited;}
    int getPowerConsumption(){return powerConsumption; }
    vector<vector<cell*>> getAdjVect(){return adjVect;}
    
    //increment population
    virtual void incPop();
    //decrement population
    void decPop();

    virtual int calcPowerConsumption();

    private:
    int posX;
    int posY;
    int pop;
    int pollution;
    bool visited;
    char cellTag;
    vector<vector<cell*>> adjVect;

    protected:
    int powerConsumption;

};

#endif