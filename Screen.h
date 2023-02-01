#pragma once
#include "Definitions.h"

class Screen
{
protected:
    char    icon;
    Pixel   pixel;
    Pixel   margin;
    Colors  colors;
public:
    static HANDLE console;
    static HANDLE keyboard;
    static Pixel gardenOffset;
    static Pixel memoryOffset;

    Screen(const Pixel&, const Pixel&);
    Screen(const char&, const Pixel&, const Pixel&);
    Screen(const char&, const Pixel&, const Pixel&, const Colors&);
    Pixel getPixel() const;
    void draw() const;
private:
    void setDrawColor() const;
    void setCursorPosition() const;
    void restoreDrawColor() const;
};

