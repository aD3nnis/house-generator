#include <iostream>
using namespace std;

#include "Room.h"

class Kitchen : public Room{
    private: 
    const float R_KITCHEN = 0.8f;
    public: 
        float get_size() const override;
};