#ifndef FIREHOUSE_H
#define FIREHOUSE_H

#include <vector>

class Firehouse {
private:
    int capacity; // Capacity of the firehouse
    int x, y; // Coordinates of the firehouse
public:
    Firehouse(int capacity, int x, int y); // Constructor
    int getCapacity(); // Getter for firehouse capacity
    int getX(); // Getter for X coordinate
    int getY(); // Getter for Y coordinate
};

#endif // FIREHOUSE_H
