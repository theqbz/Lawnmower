#include "Screen.h"

HANDLE Screen::console = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE Screen::keyboard = GetStdHandle(STD_INPUT_HANDLE);
Pixel  Screen::gardenOffset = { 0,0 };
Pixel  Screen::memoryOffset = { 0,0 };

Screen::Screen(const Pixel& pixel, const Pixel& margin) :
    pixel(pixel), margin(margin)
{
    icon = UNDEF_ICON;
    colors = UNDEF_COLOR;
}

Screen::Screen(const char& icon, const Pixel& pixel, const Pixel& margin) :
    icon(icon), pixel(pixel), margin(margin)
{
    colors = UNDEF_COLOR;
}

Screen::Screen(const char& icon, const Pixel& pixel, const Pixel& margin, const Colors& colors) :
    icon(icon), pixel(pixel), margin(margin), colors(colors) {}

Pixel Screen::getPixel() const
{
    return pixel;
}

void Screen::draw() const
{
    setCursorPosition();
    setDrawColor();
    std::cout << icon;
    restoreDrawColor();
}

void Screen::setCursorPosition() const
{
    COORD coords = { pixel.x + margin.x,pixel.y + margin.y };
    SetConsoleCursorPosition(console, coords);
}

void Screen::restoreDrawColor() const
{
    SetConsoleTextAttribute(console, 15);
}

void Screen::setDrawColor() const
{
    short color = colors.text + colors.background * 16;
    SetConsoleTextAttribute(console, color);
}
