#include <iostream>
using namespace std;

#include "Room.h"

class Bathroom : public Room
{
private:
    static constexpr float R_BATHROOM = 0.4f;

public:
    float get_default_size_ratio() override;
    Bathroom() : Room() {};
    Bathroom(const string& n) : Room(n) {}
};