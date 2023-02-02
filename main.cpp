#include "AllSimulationHeaders.h"

char doSim(int i)
{
    system("cls");
    std::cout << "GrassEater Simulation\t" << i;
    Simulation s("map2.txt");
    return s.doSimulation();
}

int main()
{
    srand((unsigned)time(NULL));
    int i = 0;
    char result = '1';
    std::vector<char> results;
    while (i < 100 && result != 'Q') {
        result = doSim(i++);
        results.push_back(result);
    }
    for (int i = 0; i < results.size(); i++)
        std::cout << i << ".: " << results[i] << "\n";
    std::cin.get();
    return 0;
}