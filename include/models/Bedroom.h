#include <iostream>
using namespace std;

#include "Room.h"

class Bedroom : public Room
{
private:
    static constexpr float R_BEDROOM = 0.7f;
    int length;
    int width;

public:
    static float default_size_ratio();
};