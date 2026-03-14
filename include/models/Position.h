#include <iostream>
using namespace std;
#include <map>
#include <tuple>

#include "Room.h"
#include "Grid.h"
#include "Livingroom.h"

class Position{
    // i need grid
    // char n = '_';
    // char s = '-';
    // char e = '!';
    // char w = '|';
    public: 
        // facilitator function
        void place_livingroom(Grid &grid, Livingroom &liv);
        // facilitator function
        void check_if_side_taken();
};