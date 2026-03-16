#ifndef KITCHEN_H
#define KITCHEN_H
#include <iostream>
#include <string>
using namespace std;

#include "Room.h"

class Kitchen : public Room
{
private:
    static constexpr float R_KITCHEN = 0.8f;

public:
    float get_default_size_ratio() override;
    Kitchen() : Room() {};
    Kitchen(const string& n) : Room(n) {}
};
#endif