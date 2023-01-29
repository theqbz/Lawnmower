#pragma once
#include "Definitions.h"

class Screen
{
protected:
    static HANDLE console;
    char icon;
    Pixel pixel;
    Colors colors;
public:
    Screen(const Pixel&);
    Screen(const char&, const Pixel&);
    Screen(const char&, const Pixel&, const Colors& color);
    void draw() const;
    void setCursorPosition() const;
    void setDrawColor() const;
};

