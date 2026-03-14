#include "../../include/models/Room.h"

void Room::set_room_sqft(float percent, float totalSqft){
    cout << "room_sqft in set: " << this->room_sqft << endl;
    this->room_sqft = (percent / 100.0f) * totalSqft; 
}
// use pointer to refer data to current object.
// since ill have a list of objects
float Room::get_room_sqft(){
    cout << "room_sqft in get: " << this->room_sqft << endl;
    return room_sqft;
}

void Room::update_dimensions(LayoutGenerator& layout_gen){
    layout_gen.calcDimensions(room_sqft, width, height);
}

void Room::display_w_h(Room& r){
    cout << "w: " << r.width << "h: " << r.height;
}

void Room::make_walls_of_room(){
    // where is dictonary made? 
    // if each room has a dictonary of coordinates then it should be initalized in room. 
    // positions n,s,e,w
    // add to its own ditconary?
    for(int x = 0; x < width; x++ ){
        for(int y =0; y < height; y++){
            if(x == 0){    
                walls[make_tuple(x,y)] = Room::N;
            }else if (x == width - 1){
                walls[make_tuple(x,y)] = Room::S;
            }else if (y == height - 1){
                walls[make_tuple(x,y)] = Room::E;
            }else if (y == 0){
                walls[make_tuple(x,y)] = Room::W;
            }else{
                 walls[make_tuple(x, y)] = ' ';
            }
        }
    }   

}
void Room::display_room_grid(){
    for(int x = 0; x < width; x++ ){
        for(int y =0; y < height; y++){
            auto key = make_tuple(x,y);
            cout << walls[key] << " "; 
        }
        cout << endl;
    }
}

