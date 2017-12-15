#include <iostream>
#include "Arenstof.h"

int main() {

    long double x = 1;
    long double y = 1;
    long double vx = 1;
    long double vy = 1;
    long double T = 100;
    int n = 8;
    int m = 2;

    long double deltaT = T / m;

    Arenstof arenstof(
        ArenstofPoint(x, y, vx, vy),
        deltaT, m);

    for (int i=0; i<m; i++)
    {
        arenstof.Update();
    }

    ArenstofPoint p (1, 2, 3, 4);
    std::cout << p << "\n";

    return 0;
}