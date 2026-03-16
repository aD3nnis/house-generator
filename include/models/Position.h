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
    vector<char> free_space;
    vector<char> taken_space;
    // map<tuple<int,int>char> 

    public: 
        // facilitator function
        void place_livingroom(Grid &grid, House &house);
        // facilitator function
        void check_if_side_taken(Grid &grid, Room &room);
        void pick_random_free_side();
        void picked_north_side(Grid &grid, Room &room);
        void picked_south_side(Grid &grid, Room &room);
        void picked_east_side(Grid &grid, Room &room);
        void picked_west_side(Grid &grid, Room &room);
};