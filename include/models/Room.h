#include <iostream>
using namespace std;
#include "../systems/LayoutGenerator.h"

#pragma once
#ifndef ROOM_H
#define ROOM_H

class Room
{
private:
    int width{};
    int height{};
    float room_sqft{};

public:
    int get_width() { return width; }
    int get_height() { return height; }
    void set_width(int w) { width = w; }
    void set_height(int h) { height = h; }

    void set_room_sqft(float percent, float totalSqft);
    float get_room_sqft();

    void update_dimensions(LayoutGenerator &layout_gen);

    virtual float get_default_size_ratio() = 0;
    virtual ~Room() = default;
};
#endif