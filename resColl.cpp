#include "resColl.h"
#include <iostream>
#include <iterator>

resColl::resColl()
{

}

void resColl::resCollect(residential *rCell)
{
    resVector.push_back(rCell);
}

//takes region and sets it to the adjacent region for every R value
void resColl::resAdj(vector<vector<cell*>> reg){

    for(int i=0;i<reg.size();i++){
        for(int j=0;j<reg[i].size();j++){
            if(reg[i][j]->getCellTag() == 'R'){
                reg[i][j]->setAdjVect(reg);
            }
        }
    }
}

void resColl::printResVect(){

    for(unsigned int i=0;i<resVector.size();i++){
        resVector.at(i)->printRes();
    }
}


//returns true if the residential cell is adjacent to a powerline, false otherwise
bool resColl::AdjPower(cell* res2)
{
    bool powerAdj = false;

    vector<vector<cell*>> resVector2 = res2->getAdjVect();

    for(int i = 0;i<resVector2.size();i++){
        for(int j = 0; j<resVector2[i].size();j++){
            if(resVector2[i][j]->getCellTag() == 'T'){
                powerAdj = true;
            }
        }
    }
    return powerAdj;
}
//returns true if adjacent to another residential cell, returns false otherwise
bool resColl::AdjRes(cell* res4)
{
    bool powerRes2 = false;

    vector<vector<cell*>> resVector4 = res4->getAdjVect();

    for(int i = 0;i<resVector4.size();i++){
        for(int j = 0; j<resVector4[i].size();j++){
            if(resVector4[i][j]->getCellTag() == 'R'){
                powerRes2 = true;
                
            }
        }
    }
    return powerRes2;
}
/*bool resColl::resEqual(cell* res6)
{
    bool equalR = false;

    vector<vector<cell*>>resVector6 = res6->getAdjVect();

    for(int i = 0;i<resVector6.size();i++){
        for(int j = 0; j<resVector6[i].size();j++){
            if(resVector4[i][j]->getCellTag() == 'R')
            {
                if()
            }
        }
    }
    return equalR;


}*/

void resColl::resGrowth(int &workers)
{
    
    for(int i=0; i<resVector.size(); i++)
    {
        if(resVector.at(i)->getPop() == 0)
        {
            if(AdjPower(resVector.at(i)) == true)
            {
                resVector.at(i)->incPop();
                workers++;
            }

        }

        if(resVector.at(i)->getPop() == 0)
        {
            if(AdjRes(resVector.at(i)) == true)
            {
                resVector.at(i)->incPop();
                workers++;
            }

        }

        /*
        if(resVector.at(i)->getPop() == 0)
        {

            resVector.at(i)->incPop();
            workers++;

        }

        if(resVector.at(i)->getPop() == 1)
        {

            resVector.at(i)->incPop();
            workers++;

        }

        if(resVector.at(i)->getPop() == 2)
        {

            resVector.at(i)->incPop();
            workers++;

        }

        if(resVector.at(i)->getPop() == 3)
        {

            resVector.at(i)->incPop();
            workers++;

        }

        if(resVector.at(i)->getPop() >= 4)
        {

            resVector.at(i)->incPop();
            workers++;

        }

        /*if(resVector.at(i)-> getPop() == 1) {
            if(AdjRes(resVector.at(i)) == true)
            {
                resVector.at(i)->incPop();
                workers++;
            }

        }*/
        else if(resVector.at(i)->getPop() == 0)
        {
            if(AdjRes(resVector.at(i)) == true) {
                resVector.at(i)->incPop();
                workers++; }
        }
        else if(resVector.at(i)->getPop() == 1)
        {
                if(AdjRes(resVector.at(i)) == true) {

                resVector.at(i)->incPop();
                workers++;}
        }
        else if(resVector.at(i)->getPop() == 2)
        {
                if(AdjRes(resVector.at(i)) == true) {

                resVector.at(i)->incPop();
                workers++;}
        }
        else if(resVector.at(i)->getPop() == 3)
        {
                if(AdjRes(resVector.at(i)) == true) {

                resVector.at(i)->incPop();
                workers++;}
        }
        else if(resVector.at(i)->getPop() >= 4)
        {
                if(AdjRes(resVector.at(i)) == true) {

                resVector.at(i)->incPop();
                workers++;}
        }

    }
}

void resColl::resDecay(int &workers)
{
    
    for(int i=0; i<resVector.size(); i++)
    {
        if(resVector.at(i)->getPop() == 2)
        {
            if(AdjPower(resVector.at(i)) == true)
            {
                resVector.at(i)->decPop();
                workers--;
            }

        }

        if(resVector.at(i)->getPop() == 3)
        {
            if(AdjRes(resVector.at(i)) == true)
            {
                resVector.at(i)->decPop();
                workers--;
            }

        }


    }
}

/*void resColl::resGone(int &workers)
{
    for(int i=0; i<resVector.size(); i++)
    {
        if(resVector.at(i)->getPop() == 2)
        {
            if(AdjPower(resVector.at(i)) == true)
            {
                resVector.at(i)= 0;
                workers = 0;
            }

        }



    }
}
*/
    /*If a cell has a population of 0 and is adjacent to a powerline in the current time step, that cell’s population will increase by 1 in the next time step
If a cell has a population of 0 and is adjacent to at least one cell with a population of at least 1, that cell’s population will increase by 1 in the next time step
If a cell has a population of 1 and is adjacent to at least two cells with a population of at least 1, that cell’s population will increase by 1 in the next time step
If a cell has a population of 2 and is adjacent to at least four cells with a population of at least 2, that cell’s population will increase by 1 in the next time step
If a cell has a population of 3 and is adjacent to at least six cells with a population of at least 3, that cell’s population will increase by 1 in the next time step
If a cell has a population of 4 and is adjacent to at least eight cells with a population of at least 4, that cell’s population will increase by 1 in the next time step*/
   

/*int resColl::howManyPoprNeighbors(residential *re)
{
    int neighborsWithPop1 = 0;
    vector<cell*> rNeighbors = re->getResNeighbors();
    for(int i=0;i<rNeighbors.size();i++){
        if(rNeighbors.at(i)->getPop() >= 1){
            neighborsWithPop1++;
        }
    }
    return neighborsWithPop1;
}

residential *resColl::resConv(cell *re)
{
    residential* resCell;
    for(int i = 0;i<resVector.size();i++){
        if(re->getCellTag() == resVector[i]->getCellTag() && re->getX() == resVector[i]->getX() && re->getY() == resVector[i]->getY()){
            resCell = resVector.at(i);
        }
    }
    return resCell;
}

residential *resColl::poprSearch(residential *re)
{
    residential* resCell1;
    vector<cell*> rNeighbors = re->getResNeighbors();
    re->setVisited(true);
    if(re->getPop() >= 0 || re->getPop() >= 1){
        resCell1 = re;
        //If power adjacent
        if(AdjPower(re) == true){
            re->incPop();

        } else if(howManyPoprNeighbors(re) == 1) {
            re->incPop();
        }

    }else if(re->getPop() == 1 ){
        if(howManyPoprNeighbors(re) >= 2){
            re->incPop();
        } 

    }else if(re->getPop() == 2 ){
        if(howManyPoprNeighbors(re) >= 4){
            re->incPop();
        } 
    }else if(re->getPop() == 3 ){
        if(howManyPoprNeighbors(re) >= 6){
            re->incPop();
        } 
    }
    else if(re->getPop() == 4 ){
        if(howManyPoprNeighbors(re) >= 8){
            re->incPop();
        } 
    }
    else {
        for(int i=0;i<rNeighbors.size();i++){
            if(!rNeighbors[i]->getVisited()){
                resCell1 = poprSearch(resConv(rNeighbors[i]));
                if(resCell1){
                    break;
                }
            }
        }
    }


    return resCell1;
}
*/