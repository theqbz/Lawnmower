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
    short      speed;

    void generateGarden(const std::string&);
    vString readMapFromFile(const std::string&);
    void drawGarden() const;
    bool endSimulation() const;
    void work();
    bool crash(const Pixel&) const;
    void moveAndCut();
    void cut(const Pixel&, const Location&);
    bool dockIsVisible() const;
    void goToDock();
    void refreshTelemetry() const;
    void clearTelemetryArea() const;
    void getUserCommand();

public:
    Simulation(const std::string&);
    ~Simulation();
    void doSimulation();
};

