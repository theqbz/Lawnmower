#pragma once
#include "Definitions.h"
#include "Lawnmower.h"
#include "Field.h"

class Simulation
{
    short gardenX, gardenY;
    short dockX, dockY;
    Pixel gardenOffset;
    Field*** garden;
    Lawnmower* robot;
    static unsigned short grassCounter;

    void generateGarden(const std::string&);
    std::vector<std::string> readMapFromFile(const std::string&);

public:
    Simulation(const std::string&);
    ~Simulation();
    void drawGarden() const;

};

