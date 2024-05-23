#include "SportsArena.h"


SportsArena::SportsArena(int x, int y){
    setTag('A');
    setX(x);
    setY(y);
    setPop(1);
    isEvent = false;
}
void SportsArena::setEvent(bool v){
    isEvent = v;
}
void SportsArena::startEvent(vector<vector<cell*>> &r){
    cout << "Event started" << endl;
    isEvent = true;
    setPop(gatherPop(r));
}
void SportsArena::endEvent(){
    cout << "Event has ended" << endl;
    isEvent = false;
    setPop(1);
}
int SportsArena::gatherPop(vector<vector<cell*>> &r){
    cout <<"Gathering Population"<<endl;
    int total = 0;
    for(int i =0;i<r.size();i++){
        for(int j = 0;j<r[i].size();j++){
            total += r[i][j]->getPop();
        }
    }
    return total;
}