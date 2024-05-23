#include "firehouse.h"

// Constructor definition
Firehouse::Firehouse(int capacity, int x, int y) {
    this->capacity = capacity;
    this->x = x;
    this->y = y;
}

// Getter function for firehouse capacity
int Firehouse::getCapacity() {
    return capacity;
}

// Getter function for X coordinate
int Firehouse::getX() {
    return x;
}

// Getter function for Y coordinate
int Firehouse::getY() {
    return y;
}
