#pragma once
#include "Screen.h"

class Field :
    public Screen
{
    bool grass;
    unsigned short progress;

    void changeIcon();

public:
    static short count;
    Field(const char&, const Pixel&);
    ~Field();
    bool isGrass();
    void cutGrass();
};

