#ifndef SPORTSARENA_H
#define SPORTSARENA_H
#include "commercial.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//Use separate class to create gatherPop, createArena, startEvent functions

//Object class to create the Arena objects
class SportsArena: public commercial{
    public:
    //Constructors
    SportsArena(int x, int y);
    
    //Setters
    void setEvent(bool v);

    //Getters
    bool getEvent(){return isEvent;}
    
    void startEvent(vector<vector<cell*>> &r);
    void endEvent();
    int gatherPop(vector<vector<cell*>> &r);

    private:
    bool isEvent;

    

};

#endif