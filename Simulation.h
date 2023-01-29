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
    bool crash(const Pixel&) const;
    void moveAndCut();
    void cut(const Pixel&, const Location&);
    void refreshTelemetry() const;

public:
    Simulation(const std::string&);
    ~Simulation();
    void drawGarden() const;
    void doSimulation();
};

