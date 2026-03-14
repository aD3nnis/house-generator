#include <iostream>
using namespace std;

#include "Room.h"

class Bathroom : public Room{
    private: 
    const float R_BATHROOM = 0.4f;
    public: 
        float get_size() const override;
};