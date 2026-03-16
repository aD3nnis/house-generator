#ifndef BEDROOM_H
#define BEDROOM_H
#include <iostream>
using namespace std;

#include "Room.h"

class Bedroom : public Room
{
private:
    static constexpr float R_BEDROOM = 0.7f;

public:
    float get_default_size_ratio() override;
    Bedroom() : Room() {};
    Bedroom(const string& n) : Room(n) {}
};
#endif