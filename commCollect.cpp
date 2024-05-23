#include "commCollect.h"
#include <iterator>
#include <iostream>
/* Collection class of all Commercial Cells:
All commercial objects are stored into a vector from a function call to collectCells then iterated through to find neighbors with a higher or lower population size*/
commCollect::commCollect(){
    hasArena = false;
}

//Collect cells that contain C as their marker and create new commercial objects with those coordinates and pass through the initial array to create an adjacency vector with neighbors
void commCollect::collectCells(commercial* cCell){
    commVector.push_back(cCell);

}
void commCollect::setHasArena(bool a){
    hasArena = a;
}

//Set adjacency for all C cells in Region
void commCollect::setAllAdj(vector<vector<cell*>> r){
    int i,j,k;

    //Sets the adjacency 2D Vector of the commercial cell
    for(i=0;i<r.size();i++){
        for(j=0;j<r[i].size();j++){
            if(r[i][j]->getCellTag() == 'C'){
                r[i][j]->setAdjVect(r);
            }
        }
    }
    //Appends all commercial neighbors of the commercial cell into the commVector
    for(k=0;k<commVector.size();k++){
        commVector[k]->setCellNeighbors();
    }
}

//Print dereferenced objects from the collection vector
void commCollect::printVector(){
    unsigned int i;
    for(i=0;i<commVector.size();i++){
        commVector.at(i)->printInfo();
    }
}


//Commercial growth function 
void commCollect::commercialGrowth(int &avWorkers, int &avGoods, vector<vector<cell*>> &region){
    arenaCheck(region);
    commercial* ch;
    //Set an initial search point for DFS algorithm
    for(int i =0;i<commVector.size();i++){
        if(commVector[i]->getVisited() == false){
            ch = commVector[i];
            break;
        } else if(i == commVector.size()-1) {
            //Reset all visited flags
            for(int j =0;j<commVector.size();j++){
                commVector[j]->setVisited(false);
            }
            ch = commVector[0];
        }
    }
    //Loop through it's neighbors
    if(ch->getCellTag() == 'C'){
        ch = popSearch(ch);
        //ch->printInfo();
    }



}

//Helper function to determine if the chosen cell is next to a powerline
bool commCollect::isPowerAdj(cell* chosen){
    bool isAdj = false;
    vector<vector<cell*>> vect = chosen->getAdjVect();
    
    for(int i = 0;i<vect.size();i++){
        for(int j = 0; j<vect[i].size();j++){
            if(vect[i][j]->getCellTag() == 'T'){
                isAdj = true;
            }
        }
    }
    return isAdj;
}
//Checks for neighbors with a population of 1 or 2
int commCollect::howManyPopNeighbors(commercial* c){
    int neighborsWithPop = 0;
    vector<cell*> cNeighbors = c->getCellNeighbors();
    for(int i=0;i<cNeighbors.size();i++){
        if(cNeighbors[i]->getPop() >= 1){
            neighborsWithPop++;
        }
    }
    return neighborsWithPop;
}
//DFS Search
commercial* commCollect::popSearch(commercial* c){
    
    //cout << "Pop Search Initiated" << endl;
    commercial* rCell;
    vector<cell*> cNeighbors = c->getCellNeighbors();
    c->setVisited(true);
    if(c->getPop() >= 0 || c->getPop() >= 1){
        rCell = c;
        //If power adjacent
        if(isPowerAdj(c) == true){
            c->incPop();

        } else if(howManyPopNeighbors(c) >= 1) {
            c->incPop();
        }

    }else if(c->getPop() == 1 ){
        if(howManyPopNeighbors(c) == 2){
            c->incPop();
        } else {
            //cout << "Does not contain 2 neighbors with population of 1 or more" << endl;
        }
    } else {
        for(int i=0;i<cNeighbors.size();i++){
            if(!cNeighbors[i]->getVisited()){
                rCell = popSearch(cellConv(cNeighbors[i]));
                if(rCell){
                    break;
                }
            }
        }
    }


    return rCell;
}
commercial* commCollect::cellConv(cell* c){
    commercial* retCell;
    for(int i = 0;i<commVector.size();i++){
        if(c->getCellTag() == commVector[i]->getCellTag() && c->getX() == commVector[i]->getX() && c->getY() == commVector[i]->getY()){
            retCell = commVector[i];
        }
    }
    return retCell;
}

//Clean vectors from all objects in the collection as well as the collection itself
void commCollect::cleanUp(){
    for(auto it = commVector.begin(); it != commVector.end();++it){
        cell* temp = *it;
        delete temp;
        
    }
    commVector.clear();
    //cout << "Commercial Collection Vector Cleared " << endl;
}
//Arena Functionality
void commCollect::arenaCheck(vector<vector<cell*>> &r){
    int count=0;
    //If all the cells have a population of 1 create an Arena
    for(int i =0;i<commVector.size();i++){
        if(commVector[i]->getPop() == 1){
            count ++;
        }
    }
    if(count == commVector.size()){
        //cout << "Arena can be made" << endl;
        createArena(r);
    }
}
void commCollect::createArena(vector<vector<cell*>> &region){
    int count = 0;
    for(int i =0;i<commVector.size();i++){
        if(commVector[i]->getPop()==1){
            count++;
        }
        if(count == 4){
            int inner = 0;
            for(int j = 0;j<region.size();j++){
                for(int k = 0;k<region[j].size();k++){
                    if(inner == 4){
                        break;
                    }
                    //Make the first 4 Commercial cells an Arena cell
                    if(region[j][k]->getCellTag() == 'C'){
                        for(int l =0;l<commVector.size();l++){
                            //If A is already made point the cell region to the main Arena obj
                            if(Arena){
                                //Point to already made Arena object
                                region[j][k] = Arena;
                            } else {
                                //Create new obj if commVector does not contain an arena obj
                                SportsArena* aCell = new SportsArena(j,k);
                                region[j][k] = aCell;
                                Arena= aCell;
                            }
                        }
                        inner++;
                    }
                }
            }
        }
    }
    hasArena = true;
}
void commCollect::startEvent(vector<vector<cell*>> &r){
    Arena->startEvent(r);
}
void commCollect::endEvent(){
    Arena->endEvent();
}

