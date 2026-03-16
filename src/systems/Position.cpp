#include "../../include/systems/Position.h"
#include "../../include/models/Room.h"
#include "../../include/models/House.h"
#include "../../include/models/Bedroom.h"
#include "../../include/models/Kitchen.h"
#include "../../include/models/Livingroom.h"
#include "../../include/models/Grid.h"

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
    free_space.clear();
    taken_space.clear();
    bool north_taken = false;
    bool south_taken = false;
    bool east_taken = false;
    bool west_taken = false;

    for (int x = 0; x < room.get_height(); x++) {
        for (int y = 0; y < room.get_width(); y++){
            // For each side, avoid including the very last point along that wall.
            if (x == 0 && y < room.get_width() - 1) {
                // Check cells directly north of the room's north wall
                auto northKey = make_tuple(room.get_anchor_x() + x - 1, room.get_anchor_y() + y);
                if (coordinates[northKey] == Room::E || coordinates[northKey] == Room::W || coordinates[northKey] == ' ' && taken_space.count(Room::N) == 0 ){
                    north_taken = true;
                }
            } else if (x == room.get_height() - 1 && y < room.get_width() - 1) {
                // Check cells directly south of the room's south wall
                auto southKey = make_tuple(room.get_anchor_x() + x + 1, room.get_anchor_y() + y);
                if (coordinates[southKey] == Room::E || coordinates[southKey] == Room::W || coordinates[southKey] == ' ' && taken_space.count(Room::S) == 0)
                {
                    south_taken = true;
                }
            } else if (y == room.get_width() - 1 && x < room.get_height() - 1) {
                // Check cells directly east of the room's east wall
                auto eastKey = make_tuple(room.get_anchor_x() + x, room.get_anchor_y() + y + 1);
                if (coordinates[eastKey] == Room::N || coordinates[eastKey] == Room::S || coordinates[eastKey] == ' ' && taken_space.count(Room::E) == 0) east_taken = true;

            } else if (y == 0 && x < room.get_height() - 1) {
                // Check cells directly west of the room's west wall
                auto westKey = make_tuple(room.get_anchor_x() + x, room.get_anchor_y() + y - 1);
                if (coordinates[westKey] == Room::N || coordinates[westKey] == Room::S || coordinates[westKey] == ' ' && taken_space.count(Room::W) == 0) west_taken = true;

            }
        }
    }
        // AFTER both loops: decide once per side
        if (north_taken) {
            taken_space.insert(Room::N);
        } else {
            free_space.insert(Room::N);
        }
    
        if (south_taken) {
            taken_space.insert(Room::S);
        } else {
            free_space.insert(Room::S);
        }
    
        if (east_taken) {
            taken_space.insert(Room::E);
        } else {
            free_space.insert(Room::E);
        }
    
        if (west_taken) {
            taken_space.insert(Room::W);
        } else {
            free_space.insert(Room::W);
        }
}

void Position::pick_random_free_side(Grid &grid, Room &room, Room &newRoom){

    // after check_if_side_taken has populated free_space
    if (!free_space.empty()) {
        int idx = rand() % free_space.size();   // random index in [0, size-1]
        char side = *next(free_space.begin(), idx);           // random free side
        if (dynamic_cast<Bedroom*>(&newRoom) != nullptr) {
        }

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

        // Helper: does this candidate have at least one free side?
        auto has_free_side = [&](Room* cand) -> bool {
            check_if_side_taken(grid, *cand);
            return !free_space.empty();
        };

        if (dynamic_cast<Bedroom*>(newRoom) != nullptr) {
            // Build lists of kitchens and livingrooms among already placed rooms
            vector<Room*> kitchens;
            vector<Room*> livingrooms;
            for (Room* r : placed) {
                if (dynamic_cast<Kitchen*>(r) != nullptr) {
                    kitchens.push_back(r);
                } else if (dynamic_cast<Livingroom*>(r) != nullptr) {
                    livingrooms.push_back(r);
                }
            }

            // coin flip: 0 = kitchens first, 1 = livingrooms first
            int preferLivingroomFirst = rand() % 2;

            auto try_list_for_anchor = [&](const vector<Room*>& rooms) -> Room* {
                for (Room* r : rooms) {
                    if (has_free_side(r)) {
                        return r;
                    }
                }
                return nullptr;
            };

            if (preferLivingroomFirst) {
                // 1) Try livingrooms first
                anchor = try_list_for_anchor(livingrooms);
                // 2) If none, then kitchens
                if (!anchor) {
                    anchor = try_list_for_anchor(kitchens);
                }
            } else {
                // 1) Try kitchens first
                anchor = try_list_for_anchor(kitchens);
                // 2) If none, then livingrooms
                if (!anchor) {
                    anchor = try_list_for_anchor(livingrooms);
                }
            }

            // 3) If still none, try any placed room with a free side
            if (!anchor) {
                for (Room* r : placed) {
                    if (has_free_side(r)) {
                        anchor = r;
                        break;
                    }
                }
            }

            // 4) Absolute fallback: just pick a random placed room
            if (!anchor && !placed.empty()) {
                anchor = placed[rand() % placed.size()];
                check_if_side_taken(grid, *anchor);
            }
        } else if (dynamic_cast<Kitchen*>(newRoom) != nullptr) {
            // Kitchens should branch off a Livingroom
            vector<Room*> livingrooms;
            for (Room* r : placed) {
                if (dynamic_cast<Livingroom*>(r) != nullptr) {
                    livingrooms.push_back(r);
                }
            }

            // 1) Prefer a livingroom that actually has a free side
            for (Room* lr : livingrooms) {
                if (has_free_side(lr)) {
                    anchor = lr;
                    break;
                }
            }

            // 2) Fallback: if no livingroom has a free side, try any placed room with a free side
            if (!anchor) {
                for (Room* r : placed) {
                    if (has_free_side(r)) {
                        anchor = r;
                        break;
                    }
                }
            }

            // 3) Absolute fallback: if still none, attach to a random placed room (if any)
            if (!anchor && !placed.empty()) {
                anchor = placed[rand() % placed.size()];
                check_if_side_taken(grid, *anchor);
            }
        } else if (dynamic_cast<Bathroom*>(newRoom) != nullptr) {
            // Bathrooms can attach to Livingroom, Bedroom, or Kitchen, but not Bathrooms
        
            vector<Room*> allowed;
            for (Room* r : placed) {
                if (dynamic_cast<Livingroom*>(r) != nullptr ||
                    dynamic_cast<Bedroom*>(r)    != nullptr ||
                    dynamic_cast<Kitchen*>(r)    != nullptr) {
                    allowed.push_back(r);
                }
            }
        
            // 1) Prefer an allowed room that actually has a free side
            for (Room* r : allowed) {
                if (has_free_side(r)) {   // same helper you already defined
                    anchor = r;
                    break;
                }
            }
            
            // 2) Fallback:
            if (!anchor) {
                for (Room* r : placed) {
                    if (has_free_side(r)) {
                        anchor = r;
                        break;
                    }
                }
            }
        
            // 3) Absolute fallback: random placed room if nothing has a free side
            if (!anchor && !placed.empty()) {
                anchor = placed[rand() % placed.size()];
                check_if_side_taken(grid, *anchor);
            }
        } else {
            // Non-bedrooms, non-kitchens can attach to any placed room
            if (!placed.empty()) {
                anchor = placed[rand() % placed.size()];
                check_if_side_taken(grid, *anchor);
            }
        }

        if (anchor) {
            pick_random_free_side(grid, *anchor, *newRoom);
        }
        placed.push_back(newRoom);
    }
}


