#include <iostream>
using namespace std;

#include "Room.h"

class Bathroom : public Room
{
private:
    static constexpr float R_BATHROOM = 0.4f;

public:
    static float default_size_ratio();
};