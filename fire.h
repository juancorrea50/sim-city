#ifndef FIRE_H
#define FIRE_H

#include <vector>
#include <utility>

class Fire {
public:
    Fire(int intensity, int x, int y);
    void spreadFire(std::vector<std::vector<int>>& regionLayout);

private:
    int intensity;
    int x;
    int y;
};

#endif // FIRE_H
