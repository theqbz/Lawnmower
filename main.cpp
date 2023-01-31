#include "AllSimulationHeaders.h"

void doSim()
{
    Simulation s("map1.txt");
    s.doSimulation();
}

int main()
{
    srand((unsigned)time(NULL));
    system("cls");
    doSim();
    std::cin.get();
    return 0;
}