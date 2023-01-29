#pragma once
#include "Definitions.h"
#include "Lawnmower.h"
#include "Field.h"

class Simulation
{
    short gardenWidth, gardenHeight;
    short dockX, dockY;
    Field*** garden;
    Lawnmower* robot;
    static unsigned short grassCounter;

    void generateGarden(const std::string&);
    std::vector<std::string> readMapFromFile(const std::string&);

public:
    Simulation(const std::string&);
    void drawGarden() const;

};

