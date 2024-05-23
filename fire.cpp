#include "fire.h"

Fire::Fire(int intensity, int x, int y) : intensity(intensity), x(x), y(y) {}

void Fire::spreadFire(std::vector<std::vector<int>>& regionLayout) {
    // Spread the fire intensity to adjacent cells
    for (int i = std::max(0, x - 1); i <= std::min((int)regionLayout.size() - 1, x + 1); ++i) {
        for (int j = std::max(0, y - 1); j <= std::min((int)regionLayout[0].size() - 1, y + 1); ++j) {
            regionLayout[i][j] += intensity;
        }
    }
}
