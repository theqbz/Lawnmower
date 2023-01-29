#include "AllSimulationHeaders.h"

void doSim()
{
    Simulation s("map1.txt");
    s.drawGarden();
}

int main()
{
    doSim();
    std::cin.get();
    return 0;
}