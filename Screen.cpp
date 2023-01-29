#include "Screen.h"

HANDLE Screen::console = GetStdHandle(STD_OUTPUT_HANDLE);

Screen::Screen(const Pixel& pixel) :
    pixel(pixel) {}

Screen::Screen(const char& icon, const Pixel& pixel) :
    icon(icon), pixel(pixel) {}

Screen::Screen(const char& icon, const Pixel& pixel, const Colors& colors) :
    icon(icon), pixel(pixel), colors(colors) {}

void Screen::draw() const
{
    setCursorPosition();
    setDrawColor();
    std::cout << icon;
}

void Screen::setCursorPosition() const
{
    COORD coords = { pixel.x,pixel.y };
    SetConsoleCursorPosition(console, coords);
}

void Screen::setDrawColor() const
{
    short color = colors.text + colors.background * 16;
    SetConsoleTextAttribute(console, color);
}
