#include "Seasons.h"
#include <iostream>

using namespace std;

bool Seasons::Scheck = false;
std::string Seasons::currentSeason = ""; // Initialize the current season as an empty string

void Seasons::SetTimeStep(bool check) {
    Scheck = check;
}

std::string Seasons::getCurrentSeason() { // get the current season
    return currentSeason;
}

void Seasons::setCurrentSeason(std::string newSeason) { // set the season
    currentSeason = newSeason;
}

void Seasons::SeasonCheck(int timeStep) {
    // Calculate the current time step within the cycle
    int currentStep = timeStep % 20;

    // Check for the current season based on the current time step
    if (currentStep >= 0 && currentStep < 5) {
        setCurrentSeason("Spring");
        Spring();
    } else if (currentStep >= 5 && currentStep < 10) {
        setCurrentSeason("Summer");
        Summer();
    } else if (currentStep >= 10 && currentStep < 15) {
        setCurrentSeason("Autumn");
        Autumn();
    } else {
        setCurrentSeason("Winter");
        Winter();
    }
}

void Seasons::Summer() {    // Implement summer-like weather conditions here
    if (Scheck) {
        cout << "It's very warm and the sun is out.\n";
    }
}

void Seasons::Autumn() {    // Implement autumn-like weather conditions here
    if (Scheck) {
        cout << "The weather is chilly and foggy, and leaves are changing color.\n";
    }
}

void Seasons::Winter() {    // Implement winter-like weather conditions here
    if (Scheck) {
        cout << "Its snowing all day and there's slight ice on the roads.\n";
    }
}

void Seasons::Spring() {    // Implement spring-like weather conditions here
    if (Scheck) {
        cout << "It's getting warmer and flowers are beginning to bloom again.\n";
    }
}
