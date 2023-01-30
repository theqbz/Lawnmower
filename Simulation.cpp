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

bool Simulation::endSimulation() const
{
    return (quit || (Field::uncutGrassCounter < 1));
}

bool Simulation::crash(const Pixel& pixel) const
{
    if (garden[pixel.y][pixel.x]->isGrass()) return false;
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

void Simulation::refreshTelemetry() const
{
    COORD c{ 0,1 };
    SetConsoleCursorPosition(Screen::console, c);
    std::cout << "                                                                                                                ";
    SetConsoleCursorPosition(Screen::console, c);
    std::cout << "remain: " << Field::uncutGrassCounter << "\t" << robot->getTelemetry();
    Sleep(50);
}

WORD Simulation::getKeystroke() const
{
    std::cin.clear();
    DWORD readCount = 0;
    INPUT_RECORD buffer[1];
    ReadConsoleInput(Screen::keyboard, buffer, 1, &readCount);
    return buffer[0].Event.KeyEvent.wVirtualKeyCode;
}

void Simulation::getUserCommand()
{
    WORD command = getKeystroke();
    if (command == VK_ESCAPE) quit = true;
}

void Simulation::generateGarden(const std::string& filename)
{
    std::vector<std::string> gardenMap = readMapFromFile(filename);
    garden = new Field**[gardenY];
    for (short y = 0; y < gardenY; y++) garden[y] = new Field*[gardenX];
    for (short y = 0; y < gardenY; y++) for (short x = 0; x < gardenX; x++) {
        Pixel pixel{ y,x };
        garden[y][x] = new Field(gardenMap[y][x], pixel, gardenOffset);
    }
}

Simulation::Simulation(const std::string& filename)
{
    gardenOffset = { 2,1 };
    generateGarden(filename);
    Pixel dock{ dockY - 1,dockX - 1 };
    robot = new Lawnmower(dock, gardenOffset);
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
    std::cout << "GrassEater Simulation\n";
    std::cout << robot->getTelemetry() << "\tremain: " << Field::uncutGrassCounter << " blocks";
    for (short y = 0; y < gardenY; y++) for (short x = 0; x < gardenX; x++) 
            garden[y][x]->draw();
    robot->draw();
}

void Simulation::doSimulation()
{
    while (!endSimulation()) {
        while (!robot->batteryLow() && !endSimulation()) {
            while (crash(robot->destination())) {
                robot->newHeading();
            }
            moveAndCut();
            refreshTelemetry();
            getUserCommand();
        }
        robot->recharge();
        refreshTelemetry();
    }
}
