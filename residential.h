#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "cell.h"
#include <vector>
#include <string>
using namespace std;


    class residential: public cell{
    
        public:
        //contains x and y values for the residential cells
        residential(int rx, int ry);

        //Set the residential neighbors into its own vector
        void printResNeighbors();
        void setResNeighbors();
        int calcPowerConsumption();
        vector<cell*> getResNeighbors(){return resNeighbors;}

        void printRes();

        vector<cell*> resNeighbors;
        private:
        

};

#endif
