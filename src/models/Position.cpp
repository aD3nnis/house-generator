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
                    free_space.push_back(Room::N);
                } 
            }else if (x == room.get_height() - 1){ 
                // Check cells directly south of the room's south wall
                auto southKey = make_tuple(room.get_anchor_x() + x + 1, room.get_anchor_y() + y);
                if (coordinates[southKey] == grid.get_empty_space()){
                    free_space.push_back(Room::S);
                } 
            }else if (y == room.get_width() - 1){
                // Check cells directly east of the room's east wall
                auto eastKey = make_tuple(room.get_anchor_x() + x, room.get_anchor_y() + y + 1);
                if (coordinates[eastKey] == grid.get_empty_space()){
                    free_space.push_back(Room::E);
                }
            }else if (y == 0){
                // Check cells directly west of the room's west wall
                auto westKey = make_tuple(room.get_anchor_x() + x, room.get_anchor_y() + y - 1);
                if (coordinates[westKey] == grid.get_empty_space()){
                    free_space.push_back(Room::W);
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
    newRoom.set_anchor(room.get_anchor_x() - newRoom.get_height() + 1, room.get_anchor_y());
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < newRoom.get_height(); x++) {
        for (int y = 0; y < newRoom.get_width(); y++){
            auto key = make_tuple(newRoom.get_anchor_x() + x, newRoom.get_anchor_y() + y);
            auto key2 = make_tuple(x,y);
            coordinates[key] = newRoom.get_room()[key2];
        }
    }
}

void Position::picked_south_side(Grid &grid, Room &room, Room &newRoom){
    // Place newRoom directly below room: its top edge touches room's bottom edge
    newRoom.set_anchor(room.get_anchor_x() + room.get_height() - 1, room.get_anchor_y());
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < newRoom.get_height(); x++) {
        for (int y = 0; y < newRoom.get_width(); y++){
            auto key = make_tuple(newRoom.get_anchor_x() + x, newRoom.get_anchor_y() + y);
            auto key2 = make_tuple(x,y);
            coordinates[key] = newRoom.get_room()[key2];
        }
    }
}
void Position::picked_east_side(Grid &grid, Room &room, Room &newRoom){
    // Place newRoom directly to the right of room: its left edge touches room's right edge
    newRoom.set_anchor(room.get_anchor_x(), room.get_anchor_y() + room.get_width() - 1);
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < newRoom.get_height(); x++) {
        for (int y = 0; y < newRoom.get_width(); y++){
            auto key = make_tuple(newRoom.get_anchor_x() + x, newRoom.get_anchor_y() + y);
            auto key2 = make_tuple(x,y);
            coordinates[key] = newRoom.get_room()[key2];
        }
    }
}
void Position::picked_west_side(Grid &grid, Room &room, Room &newRoom){
    // Place newRoom directly to the left of room: its right edge touches room's left edge
    newRoom.set_anchor(room.get_anchor_x(), room.get_anchor_y() - newRoom.get_width() + 1);
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < newRoom.get_height(); x++) {
        for (int y = 0; y < newRoom.get_width(); y++){
            auto key = make_tuple(newRoom.get_anchor_x() + x, newRoom.get_anchor_y() + y);
            auto key2 = make_tuple(x,y);
            coordinates[key] = newRoom.get_room()[key2];
        }
    }
}

// rooms_to_place: the rooms you still need to position (unplaced)
// placed: rooms already placed on the grid (anchors you can attach to)
void Position::place_rooms_random(Grid& grid, vector<Room*>& placed, vector<Room*>& rooms_to_place)
{
    for (Room* newRoom : rooms_to_place) {

        Room* anchor = nullptr;

        // If it's a Bedroom, only choose anchors that are Kitchen or Livingroom
        if (dynamic_cast<Bedroom*>(newRoom) != nullptr) {
            vector<Room*> allowed;
            for (Room* r : placed) {
                if (dynamic_cast<Kitchen*>(r) != nullptr ||
                    dynamic_cast<Livingroom*>(r) != nullptr) {
                    allowed.push_back(r);
                }
            }
            // Fallback in case none found (optional, but safe)
            if (!allowed.empty()) {
                anchor = allowed[rand() % allowed.size()];
            } else {
                anchor = placed[rand() % placed.size()];
            }
        } else {
            // non‑bedrooms can attach to anything
            anchor = placed[rand() % placed.size()];
        }

        check_if_side_taken(grid, *anchor);
        pick_random_free_side(grid, *anchor, *newRoom);
        placed.push_back(newRoom);
    }
}