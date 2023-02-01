#include "Simulation.h"

Simulation::Simulation(const std::string& filename)
{
    gardenOffset = { 2,13 };
    generateGarden(filename);
    Pixel dock{ dockY - 1,dockX - 1 };
    robot = new Lawnmower({ dockY,dockX }, gardenOffset);
    quit = false;
    speed = SPEED_DEFAULT;
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

void Simulation::doSimulation()
{
    drawGarden();
    while (!endSimulation()) {
        while (!robot->batteryLow() && !endSimulation()) work();
        while (!dockIsVisible() && !endSimulation()) work();
        if (endSimulation()) return;
        goToDock();
        refreshTelemetry();
    }
}

void Simulation::generateGarden(const std::string& filename)
{
    vString gardenMap = readMapFromFile(filename);
    garden = new Field**[gardenY];
    for (short y = 0; y < gardenY; y++) garden[y] = new Field*[gardenX];
    for (short y = 0; y < gardenY; y++) for (short x = 0; x < gardenX; x++) 
        garden[y][x] = new Field(gardenMap[y][x], { y,x }, gardenOffset);
}

vString Simulation::readMapFromFile(const std::string& filename)
{
    vString       map;
    std::ifstream file(filename);
    std::string   line;
    while (file >> line) map.push_back(line);
    file.close();
    gardenX = (short)map[0].length();
    gardenY = (short)map.size();
    for (short y = 0; y < map.size(); y++)
        if (map[y].find(MAP_DOCK_ICON) != std::string::npos) {
            dockY = y;
            dockX = (short)map[y].find(MAP_DOCK_ICON);
        }
    return map;
}

void Simulation::drawGarden() const
{
    system("cls");
    std::cout << "GrassEater Simulation";
    for (short y = 0; y < gardenY; y++) for (short x = 0; x < gardenX; x++) 
            garden[y][x]->draw();
    robot->draw();
}

bool Simulation::endSimulation() const
{
    return (quit || Field::uncutGrassCounter < 1 || robot->batteryEmpty());
}

void Simulation::work()
{
    while (crash(robot->destination())) robot->newHeading();
    moveAndCut();
    refreshTelemetry();
    getUserCommand();
}

bool Simulation::crash(const Pixel& pixel) const
{
    if (garden[pixel.y][pixel.x]->isAwailable()) return false;
    else return true;
}

void Simulation::moveAndCut()
{
    Pixel prewiousPixel = robot->getPixel();
    Pixel destination{ 0,0 };
    Location offset = robot->move(destination);
    cut(destination, offset);
    robot->draw();
    garden[prewiousPixel.y][prewiousPixel.x]->draw();
}

void Simulation::cut(const Pixel& pixel, const Location& offset)
{
    garden[pixel.y][pixel.x]->cutGrass((1-abs(offset.y))*(1-abs(offset.x)));
    if (offset.y > 0) {
        garden[pixel.y + 1][pixel.x]->cutGrass(abs(offset.y) * (1 - abs(offset.x)));
        if (offset.x > 0) {
            garden[pixel.y + 1][pixel.x + 1]->cutGrass(abs(offset.y) * abs(offset.x));
            garden[pixel.y][pixel.x + 1]->cutGrass((1 - abs(offset.y)) * abs(offset.x));
        }
        else if (offset.x < 0) {
            garden[pixel.y + 1][pixel.x - 1]->cutGrass(abs(offset.y) * abs(offset.x));
            garden[pixel.y][pixel.x - 1]->cutGrass((1 - abs(offset.y)) * abs(offset.x));
        }
    }
    else if (offset.y < 0) {
        garden[pixel.y - 1][pixel.x]->cutGrass(abs(offset.y) * (1 - abs(offset.x)));
        if (offset.x > 0) {
            garden[pixel.y - 1][pixel.x + 1]->cutGrass(abs(offset.y) * abs(offset.x));
            garden[pixel.y][pixel.x + 1]->cutGrass((1 - abs(offset.y)) * abs(offset.x));
        }
        else if (offset.x < 0) {
            garden[pixel.y - 1][pixel.x - 1]->cutGrass(abs(offset.y) * abs(offset.x));
            garden[pixel.y][pixel.x - 1]->cutGrass((1 - abs(offset.y)) * abs(offset.x));
        }
    }
}

bool Simulation::dockIsVisible() const
{
    // az irány nem megfelelõ még
    Pixel    dock         = { dockY,dockX };
    Pixel    nextPixel    = robot->getPixel();
    float    testHeading  = robot->lineToDock();
    Location testLocation = robot->getLocation();
    while (!crash(nextPixel) && !(nextPixel == dock)) {
        testLocation = robot->testMove(testLocation, testHeading);
        nextPixel    = robot->testDestination(testLocation, testHeading);
    }
    if (nextPixel == dock) return true;
    return false;
}

void Simulation::goToDock()
{
    Pixel dock{ dockY,dockX };
    while (!(robot->getPixel() == dock)) {
        Pixel previousPixel = robot->getPixel();
        robot->moveToDock();
        robot->draw();
        garden[previousPixel.y][previousPixel.x]->draw();
        refreshTelemetry();
    }
    robot->recharge();
}

void Simulation::refreshTelemetry() const
{
    COORD c{ 1,2 };
    SetConsoleCursorPosition(Screen::console, c);
    clearTelemetryArea();
    SetConsoleCursorPosition(Screen::console, c);
    robot->printTelemetry();
    if (Field::uncutGrassCounter == 0) std::cout << "\n\n COMPLETE!\n";
    else std::cout << "\nremain:\n" << Field::uncutGrassCounter << " blocks";
    Sleep(speed);
}

void Simulation::clearTelemetryArea() const
{
    short rows = 14;
    for (short y = 0; y < rows; y++) {
        for (short x = 0; x < gardenOffset.x-1; x++) {
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

void Simulation::getUserCommand()
{
    if (GetAsyncKeyState(VK_ESCAPE)) quit = true;
    if (GetAsyncKeyState(VK_UP)) changeSpeed('+');
    if (GetAsyncKeyState(VK_DOWN)) changeSpeed('-');
}

void Simulation::changeSpeed(const char& command)
{
    if (command == '+') {
        if (speed == SPEED_MAX) return;
        speed -= 10;
        return;
    }
    if (speed = SPEED_MIN) return;
    speed += 10;
}
