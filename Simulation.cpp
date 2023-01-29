#include "Simulation.h"


std::vector<std::string> Simulation::readMapFromFile(const std::string& filename)
{
    std::vector<std::string> map;
    std::ifstream file(filename);
    std::string line;
    file >> gardenX >> gardenY >> dockX >> dockY;
    while (file >> line) map.push_back(line);
    file.close();
    return map;
}

void Simulation::generateGarden(const std::string& filename)
{
    std::vector<std::string> gardenMap = readMapFromFile(filename);
    garden = new Field**[gardenY];
    for (short y = 0; y < gardenY; y++) garden[y] = new Field*[gardenX];
    for (short y = 0; y < gardenY; y++) for (short x = 0; x < gardenX; x++) {
        Pixel pixel{ y,x };
        garden[y][x] = new Field(gardenMap[y][x], pixel + gardenOffset);
    }
}

Simulation::Simulation(const std::string& filename)
{
    gardenOffset = { 2,0 };
    generateGarden(filename);
    Pixel dock{ dockY - 1,dockX - 1 };
    robot = new Lawnmower(dock + gardenOffset);
}

Simulation::~Simulation()
{
    for (short y = 0; y < gardenY; y++) {
        for (short x = 0; x < gardenX; x++) {
            delete garden[y][x];
        }
        delete[] garden[y];
    }
    delete[] garden;
    delete robot;
}

void Simulation::drawGarden() const
{
    std::cout << "GrassEater Simulation";
    for (short y = 0; y < gardenY; y++) for (short x = 0; x < gardenX; x++) 
            garden[y][x]->draw();
    robot->draw();
}
