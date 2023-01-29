#include "AllSimulationHeaders.h"

void doSim()
{
    Simulation s("map1.txt");
    s.drawGarden();
    std::cout << "\n\ndo:" << Field::count << "\n";
}

int main()
{
    doSim();
    std::cout << "\n\nmain:" << Field::count << "\n";
    return 0;
}