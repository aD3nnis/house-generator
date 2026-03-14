#include <iostream>
#include <map> // for dict
#include <tuple> // for make_tuple member function
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
    map<tuple<int,int>,char> walls;

public:
    static const char N = '_';
    static const char S = '-';
    static const char E = '!';
    static const char W = '|';

    int get_width() { return width; }
    int get_height() { return height; }
    void set_width(int w) { width = w; }
    void set_height(int h) { height = h; }

    void set_room_sqft(float percent, float totalSqft);
    float get_room_sqft();

    void update_dimensions(LayoutGenerator &layout_gen);

    void display_w_h(Room& r);
    void make_walls_of_room();
    void display_room_grid();

    virtual float get_default_size_ratio() = 0;
    virtual ~Room() = default;
    
};
#endif