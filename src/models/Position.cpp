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
                auto key = make_tuple(grid.get_middle_grid_r()+x,grid.get_middle_grid_r()+ y);
                auto key2 = make_tuple(x,y);
                coordinates[key] = house.get_livingroom().get_room()[key2];
            }
        }
}
        // facilitator function
void Position::check_if_side_taken(){
        // if '|' check 
        }