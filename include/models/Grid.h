#pragma once
#include <iostream>
#include <map>
#include <tuple>
using namespace std;

// dots mean empty - eventually i should put space as empty but for now visually i can see it better
class Grid{
    private:
        map<tuple<int,int>,char> coordinates;
        int side = 50;
        int middle_of_grid_r = (side/2)-5; // 5 is abitrary
    public: 
        void set_coordinates(){
            for(int x = 0; x < side; x++ ){
                for(int y =0; y < side; y++){
                    coordinates[make_tuple(x,y)] = '.';
                }
            }
        }
        int get_middle_grid_r(){
            return middle_of_grid_r;
        }
        map<tuple<int,int>,char>& get_coordinates(){
            return coordinates;
        }
        void display_grid(){
            for(int x = 0; x < side; x++ ){
                for(int y =0; y < side; y++){
                    auto key = make_tuple(x,y);
                    cout << coordinates[key] << " "; 
                }
                cout << endl;
            }
        }
};