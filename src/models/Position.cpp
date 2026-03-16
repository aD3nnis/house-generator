#include "../../include/models/Position.h"
#include "../../include/models/Room.h"
#include "../../include/models/House.h"

void Position::place_livingroom(Grid &grid, House &house){
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    house.get_livingroom().set_anchor(grid.get_middle_grid_r(), grid.get_middle_grid_r());
        for (int x = 0; x < house.get_livingroom().get_height(); x++) {
            for (int y = 0; y < house.get_livingroom().get_width(); y++){
                auto key = make_tuple(house.get_livingroom().get_anchor_x()+ x ,house.get_livingroom().get_anchor_y()+ y);
                auto key2 = make_tuple(x,y);
                coordinates[key] = house.get_livingroom().get_room()[key2];
            }
        }
}
        // facilitator function
void Position::check_if_side_taken(Grid &grid, Room &room){
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();

    for (int x = 0; x < room.get_height(); x++) {
        cout << endl;
        for (int y = 0; y < room.get_width(); y++){
            if(x == 0){ 
                // Check cells directly north of the room's north wall
                auto northKey = make_tuple(room.get_anchor_x() + x - 1, room.get_anchor_y() + y);
                if (coordinates[northKey] == grid.get_empty_space()){
                    cout << "freeNorth";
                    free_space.push_back(Room::N);
                } else {
                    cout << "takenNorth";
                }
            }else if (x == room.get_height() - 1){ 
                // Check cells directly south of the room's south wall
                auto southKey = make_tuple(room.get_anchor_x() + x + 1, room.get_anchor_y() + y);
                if (coordinates[southKey] == grid.get_empty_space()){
                    cout << "freeSouth";
                    free_space.push_back(Room::S);
                } else {
                    cout << "takenSouth";
                }

            }else if (y == room.get_width() - 1){
                // Check cells directly east of the room's east wall
                auto eastKey = make_tuple(room.get_anchor_x() + x, room.get_anchor_y() + y + 1);
                if (coordinates[eastKey] == grid.get_empty_space()){
                    cout << "freeEast"; 
                    free_space.push_back(Room::E);
                } else {
                    cout << "takenEast";
                }

            }else if (y == 0){
                // Check cells directly west of the room's west wall
                auto westKey = make_tuple(room.get_anchor_x() + x, room.get_anchor_y() + y - 1);
                if (coordinates[westKey] == grid.get_empty_space()){
                    cout << "freeWest"; 
                    free_space.push_back(Room::W);
                } else {
                    cout << "takenWest";
                }

            }
        }
    }
}

void Position::pick_random_free_side(Grid &grid, Room &room, Room &newRoom){

    // after check_if_side_taken has populated free_space
    if (!free_space.empty()) {
        int idx = rand() % free_space.size();   // random index in [0, size-1]
        char side = free_space[idx];           // random free side

        if (side == Room::N) {
            picked_north_side(grid, room, newRoom);
        } else if (side == Room::S) {
            picked_south_side(grid, room, newRoom);
        } else if (side == Room::E) {
            picked_east_side(grid, room, newRoom);
        } else if (side == Room::W) {
            picked_west_side(grid, room, newRoom);
        }
    }
    free_space.clear();
}

void Position::picked_north_side(Grid &grid, Room &room, Room &newRoom){
    // Place newRoom directly above room: its bottom edge touches room's top edge
    newRoom.set_anchor(room.get_anchor_x() - newRoom.get_height(), room.get_anchor_y());
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < newRoom.get_height(); x++) {
        for (int y = 0; y < newRoom.get_width(); y++){
            auto key = make_tuple(newRoom.get_anchor_x() + x + 1, newRoom.get_anchor_y() + y);
            auto key2 = make_tuple(x,y);
            coordinates[key] = newRoom.get_room()[key2];
        }
    }
}

void Position::picked_south_side(Grid &grid, Room &room, Room &newRoom){
    // Place newRoom directly below room: its top edge touches room's bottom edge
    newRoom.set_anchor(room.get_anchor_x() + room.get_height(), room.get_anchor_y());
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < newRoom.get_height(); x++) {
        for (int y = 0; y < newRoom.get_width(); y++){
            auto key = make_tuple(newRoom.get_anchor_x() + x - 1, newRoom.get_anchor_y() + y);
            auto key2 = make_tuple(x,y);
            coordinates[key] = newRoom.get_room()[key2];
        }
    }
}
void Position::picked_east_side(Grid &grid, Room &room, Room &newRoom){
    // Place newRoom directly to the right of room: its left edge touches room's right edge
    newRoom.set_anchor(room.get_anchor_x(), room.get_anchor_y() + room.get_width());
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < newRoom.get_height(); x++) {
        for (int y = 0; y < newRoom.get_width(); y++){
            auto key = make_tuple(newRoom.get_anchor_x() + x, newRoom.get_anchor_y() + y - 1);
            auto key2 = make_tuple(x,y);
            coordinates[key] = newRoom.get_room()[key2];
        }
    }
}
void Position::picked_west_side(Grid &grid, Room &room, Room &newRoom){
    // Place newRoom directly to the left of room: its right edge touches room's left edge
    newRoom.set_anchor(room.get_anchor_x(), room.get_anchor_y() - newRoom.get_width());
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < newRoom.get_height(); x++) {
        for (int y = 0; y < newRoom.get_width(); y++){
            auto key = make_tuple(newRoom.get_anchor_x() + x, newRoom.get_anchor_y() + y + 1);
            auto key2 = make_tuple(x,y);
            coordinates[key] = newRoom.get_room()[key2];
        }
    }
}

