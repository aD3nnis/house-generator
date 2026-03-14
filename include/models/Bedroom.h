#include <iostream>
using namespace std;

#include "Room.h"

class Bedroom : public Room{
    private: 
    const float R_BEDROOM = 0.7f;
    public: 
    float get_size() const override;
};