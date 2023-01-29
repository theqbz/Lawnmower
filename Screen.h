#pragma once
#include "Definitions.h"

class Screen
{
protected:
    char    icon;
    Pixel   pixel;
    Colors  colors;
public:
    Screen(const Pixel&);
    Screen(const char&, const Pixel&);
    Screen(const char&, const Pixel&, const Colors&);
    void draw() const;
private:
    static HANDLE console;
    void setDrawColor() const;
    void setCursorPosition() const;
    void restoreDrawColor() const;
};

