#include <iostream>
using namespace std;
#include <map>
#include <tuple>

#include "Room.h"
#include "Grid.h"
#include "Livingroom.h"

class Position{
    // i need grid
    char n = '_';
    char s = '-';
    char e = '!';
    char w = '|';
    public: 

        // facilitator function
        void place_livingroom(Grid &grid, Livingroom &liv){
            map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
            cout << endl;
            int x_min = grid.get_middle_grid_r();
            int x_max = liv.get_width() + grid.get_middle_grid_r() - 1;
            int x_mid = liv.get_width()/2 + grid.get_middle_grid_r();
            int y_min = grid.get_middle_grid_r();
            int y_max = liv.get_height() + grid.get_middle_grid_r() - 1;
            int y_mid = liv.get_height()/2 + grid.get_middle_grid_r();
            for (int x = x_min; x <= x_max; x++) {
                for (int y = y_min; y <= y_max; y++) {
                    if( x == x_mid && y == y_mid ){
                        coordinates[make_tuple(x, y)] = 'L';
                    }
                    else if (x == x_min) {
                        coordinates[make_tuple(x, y)] = n;
                    }else if(x == x_max){
                         coordinates[make_tuple(x, y)] = s;
                    }else if (y == y_min){
                         coordinates[make_tuple(x, y)] = w;
                    } else if(y == y_max){
                         coordinates[make_tuple(x, y)] = e;
                    } else{
                        coordinates[make_tuple(x, y)] = ' ';
                    }
                }
            }
          //  grid.display_grid();
        }
        // facilitator function
        void check_if_side_taken(){

        }
};