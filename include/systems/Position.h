#pragma once

#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <set>
#include <vector>
#include <functional>

using namespace std;

#include "../models/Room.h"
#include "../models/Grid.h"
#include "../models/Livingroom.h"
#include "../models/House.h"

class Position{
    set<char> free_space;
    set<char> taken_space;

    public:
        // facilitator function
        void place_livingroom(Grid &grid, House &house);
        // facilitator function
        void check_if_side_taken(Grid &grid, Room &room);
        void pick_random_free_side(Grid &grid, Room &room, Room &newRoom);

        void picked_north_side(Grid &grid, Room &room, Room &newRoom);
        void picked_south_side(Grid &grid, Room &room, Room &newRoom);
        void picked_east_side(Grid &grid, Room &room, Room &newRoom);
        void picked_west_side(Grid &grid, Room &room, Room &newRoom);
        void place_rooms_random(Grid& grid, vector<Room*>& placed, vector<Room*>& rooms_to_place);
};
