#include <iostream>
using namespace std;

#include "Room.h"

class Kitchen : public Room
{
private:
    static constexpr float R_KITCHEN = 0.8f;

public:
    float get_default_size_ratio() override;
};