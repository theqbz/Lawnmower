#include "AllSimulationHeaders.h"

void doSim()
{
    Simulation s("map1.txt");
    s.drawGarden();
    s.doSimulation();
}

int main()
{
    srand((unsigned)time(NULL));
    doSim();
    std::cin.get();
    return 0;
}