#include "Simulation.h"


std::vector<std::string> Simulation::readMapFromFile(const std::string& filename)
{
    std::vector<std::string> map;
    std::ifstream file(filename);
    std::string line;
    file >> gardenHeight >> gardenWidth >> dockX >> dockY;
    while (file >> line) map.push_back(line);
    file.close();
    return map;
}

void Simulation::generateGarden(const std::string& filename)
{
    std::vector<std::string> gardenMap = readMapFromFile(filename);
    garden = new Field * *[gardenHeight];
    for (short row = 0; row < gardenHeight; row++) garden[row] = new Field * [gardenWidth];
    for (short row = 0; row < gardenHeight; row++) for (short col = 0; col < gardenWidth; col++) {
        Pixel pixel{ col,row };
        garden[row][col] = new Field(gardenMap[row][col], pixel);
    }
}

Simulation::Simulation(const std::string& filename)
{
    generateGarden(filename);
}

void Simulation::drawGarden() const
{
    for (short y = 0; y < gardenHeight; y++) {
        for (short x = 0; x < gardenWidth; x++) {
            garden[x][y]->draw();
        }
        std::cout << "\n";
    }
}
