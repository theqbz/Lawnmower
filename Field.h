#pragma once
#include "Screen.h"

class Field :
    public Screen
{
    bool  grass;
    short progress;
    void updateIcon();
public:
    static unsigned short uncutGrassCounter;
    Field(const char&, const Pixel&, const Pixel&);
    ~Field();
    bool isGrass();
    void cutGrass(const float&);
};

