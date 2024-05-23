#ifndef DISASTER_H
#define DISASTER_H

#include "residential.h"
#include <vector>
#include <string>
using namespace std;


    class disaster {
    
        public:

        //disaster will happen every 5 time steps, will check each time step in main
        disaster();
        //function to decrease the current residential population
        void Aftermath();
        void Crater();
        //outputs emergency message 
        void Emergency();

        private:



};

#endif
