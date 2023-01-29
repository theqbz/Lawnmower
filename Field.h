#pragma once
#include "Screen.h"

class Field :
    public Screen
{
    bool grass;
    unsigned short progress;

    void changeIcon();

public:
    Field(const char&, const Pixel&);
    bool isGrass();
    void cutGrass();
};

