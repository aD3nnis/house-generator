#include <iostream>
using namespace std;

#include "Room.h"


class Livingroom : public Room{
    private: 
    const float R_LIVINGROOM = 0.8f;
    public: 
        float get_size() const override;
};