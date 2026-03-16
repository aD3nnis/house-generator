#pragma once
#include <iostream>
#include <map>
#include <tuple>
using namespace std;

// dots mean empty - eventually i should put space as empty but for now visually i can see it better
class Grid{
    private:
        map<tuple<int,int>,char> coordinates;
        int grid_side;
        int middle_of_grid_r; // top right corner of rooms
        char empty_space = '.';
        char display_empty_space = ' ';
    public: 
        Grid(){
            grid_side = 50;
            middle_of_grid_r = (grid_side/2)-5;  // 5 is abitrary
            set_coordinates(coordinates);
        }
        void set_coordinates(map<tuple<int,int>,char> &coordinates_copy){ // coordinate nickname
            for(int x = 0; x < grid_side; x++ ){
                for(int y =0; y < grid_side; y++){
                    coordinates_copy[make_tuple(x,y)] = empty_space;
                }
            }
        }
        int get_middle_grid_r(){
            return middle_of_grid_r;
        }
        map<tuple<int,int>,char>& get_coordinates(){
            return coordinates;
        }
        char get_empty_space(){
            return empty_space;
        }
        void display_grid(){
            cout << endl;
            for(int x = 0; x < grid_side; x++ ){
                for(int y = 0; y < grid_side; y++){
                    auto key = make_tuple(x,y);
                    char c = coordinates[key];
                    // Show empty cells as spaces, but keep logic using '.'
                    if (c == empty_space) c = display_empty_space;
                    cout << c << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
};