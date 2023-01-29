#pragma once
#include "Definitions.h"
#include "Lawnmower.h"
#include "Field.h"

class Simulation
{
    short      gardenX, gardenY;
    short      dockX, dockY;
    Pixel      gardenOffset;
    Field***   garden;
    Lawnmower* robot;
    bool       quit;

    void generateGarden(const std::string&);
    std::vector<std::string> readMapFromFile(const std::string&);
    bool endSimulation() const;
    bool crush(const Pixel&) const;

public:
    Simulation(const std::string&);
    ~Simulation();
    void drawGarden() const;
    void doSimulation();
};

