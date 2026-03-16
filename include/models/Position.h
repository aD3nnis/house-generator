#include <iostream>
using namespace std;
#include <map>
#include <tuple>

#include "Room.h"
#include "Grid.h"
#include "Livingroom.h"
#include "House.h"

class Position{
    // i need grid

    public: 
        // facilitator function
        void place_livingroom(Grid &grid, House &house);
        // facilitator function
        void check_if_side_taken();
};