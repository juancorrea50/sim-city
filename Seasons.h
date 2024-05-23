#ifndef SEASONS_H
#define SEASONS_H

#include <string> // Include the <string> header for std::string

class Seasons {

public:
    static void SetTimeStep(bool check);
    static void SeasonCheck(int timeStep);
    static void Summer();
    static void Autumn();
    static void Winter();
    static void Spring();
    static std::string getCurrentSeason(); // Declaration for getting the current season
    static void setCurrentSeason(std::string newSeason); // Declaration for setting the current season

private:
    static bool Scheck; // Variable to check the time step of the simulation
    static std::string currentSeason; // Variable to store the current season

};

#endif // SEASONS_H
