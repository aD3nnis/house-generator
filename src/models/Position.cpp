#include "../../include/models/Position.h"
#include "../../include/models/Room.h"
#include "../../include/models/House.h"

void Position::place_livingroom(Grid &grid, House &house){
            map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
            // cout << endl;
            // int x_min = grid.get_middle_grid_r();
            // int x_max = liv.get_width() + grid.get_middle_grid_r() - 1;
            // int x_mid = liv.get_width()/2 + grid.get_middle_grid_r();
            // int y_min = grid.get_middle_grid_r();
            // int y_max = liv.get_height() + grid.get_middle_grid_r() - 1;
            // int y_mid = liv.get_height()/2 + grid.get_middle_grid_r();
          //  grid.display_grid();
        for (int x = 0; x < house.get_livingroom().get_height(); x++) {
            for (int y = 0; y < house.get_livingroom().get_width(); y++){
                auto key = make_tuple(grid.get_middle_grid_r()+ x ,grid.get_middle_grid_r()+ y);
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
                auto northKey = make_tuple(grid.get_middle_grid_r() + x - 1, grid.get_middle_grid_r() + y);
                if (coordinates[northKey] == grid.get_empty_space()){
                    cout << "freeNorth";
                } else {
                    cout << "takenNorth";
                }
            }else if (x == room.get_height() - 1){ 
                // Check cells directly south of the room's south wall
                auto southKey = make_tuple(grid.get_middle_grid_r() + x + 1, grid.get_middle_grid_r() + y);
                if (coordinates[southKey] == grid.get_empty_space()){
                    cout << "freeSouth";
                } else {
                    cout << "takenSouth";
                }

            }else if (y == room.get_width() - 1){
                // Check cells directly east of the room's east wall
                auto eastKey = make_tuple(grid.get_middle_grid_r() + x, grid.get_middle_grid_r() + y + 1);
                if (coordinates[eastKey] == grid.get_empty_space()){
                    cout << "freeEast";
                } else {
                    cout << "takenEast";
                }

            }else if (y == 0){
                // Check cells directly west of the room's west wall
                auto westKey = make_tuple(grid.get_middle_grid_r() + x, grid.get_middle_grid_r() + y - 1);
                if (coordinates[westKey] == grid.get_empty_space()){
                    cout << "freeWest";
                } else {
                    cout << "takenWest";
                }

            }
        }
    }
}

void Position::pick_random_free_side(){
    // we pick N yeah!

}

void Position::picked_north_side(Grid &grid, Room &room){
    // if north we want x - height of new room to start and y same 
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < room.get_height(); x++) {
            for (int y = 0; y < room.get_width(); y++){
                auto key = make_tuple(grid.get_middle_grid_r()+ x - room.get_height() + 1, grid.get_middle_grid_r()+ y);
                auto key2 = make_tuple(x,y);
                coordinates[key] = room.get_room()[key2];
            }
        }
}

void Position::picked_south_side(Grid &grid, Room &room){
    // if north we want x - height of new room to start and y same 
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < room.get_height(); x++) {
            for (int y = 0; y < room.get_width(); y++){
                auto key = make_tuple(grid.get_middle_grid_r()+ x + room.get_height() - 1, grid.get_middle_grid_r()+ y);
                auto key2 = make_tuple(x,y);
                coordinates[key] = room.get_room()[key2];
            }
    }
}
void Position::picked_east_side(Grid &grid, Room &room){
    // if north we want x - height of new room to start and y same 
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < room.get_height(); x++) {
            for (int y = 0; y < room.get_width(); y++){
                auto key = make_tuple(grid.get_middle_grid_r()+ x, grid.get_middle_grid_r()+ y + room.get_width() - 1);
                auto key2 = make_tuple(x,y);
                coordinates[key] = room.get_room()[key2];
            }
    }
}
void Position::picked_west_side(Grid &grid, Room &room){
    // if north we want x - height of new room to start and y same 
    map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
    for (int x = 0; x < room.get_height(); x++) {
            for (int y = 0; y < room.get_width(); y++){
                auto key = make_tuple(grid.get_middle_grid_r()+ x, grid.get_middle_grid_r()+ y - room.get_width() + 1);
                auto key2 = make_tuple(x,y);
                coordinates[key] = room.get_room()[key2];
            }
    }
}

