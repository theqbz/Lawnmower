#include "AllSimulationHeaders.h"

void doSim()
{
    Simulation s("map2.txt");
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