#include <iostream>
using namespace std;
#include <map>
#include <tuple>

#include "Room.h"
#include "Grid.h"
#include "Livingroom.h"

class Position{
    // i need grid
    char s = '_';
    char n = '_';
    char e = '|';
    char w = '|';
    public: 
        void place_livingroom(Grid &grid, Livingroom &liv){
            //(20,20 to start)
            char x = '.';
            // grid tuple start at 20,20
            map<tuple<int,int>,char>& coordinates = grid.get_coordinates();
            cout << endl;
            for(int i = 20; i < liv.get_width()+20; i++){
                for(int j =20; j < liv.get_height()+20; j++){
                  coordinates[make_tuple(i,j)] = '_';
                }
                cout << endl;
            }
            //swap(x,s);
            grid.display_grid();
        }
};