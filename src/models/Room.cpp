#include "../../include/models/Room.h"

void Room::set_room_sqft(float percent, float totalSqft){
    this->room_sqft = (percent / 100.0f) * totalSqft; 
}
// use pointer to refer data to current object.
// since ill have a list of objects
float Room::get_room_sqft(){
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
    for(int x = 0; x < height; x++ ){
        for(int y =0; y < width; y++){
            if(x == 0){    
                walls[make_tuple(x,y)] = Room::N;
            }else if (x == height - 1){
                walls[make_tuple(x,y)] = Room::S;
            }else if (y == width - 1){
                walls[make_tuple(x,y)] = Room::E;
            }else if (y == 0){
                walls[make_tuple(x,y)] = Room::W;
            }else{
                 walls[make_tuple(x, y)] = ' ';
            }
        }
    }   

}
void Room::place_name_in_room(){
    auto key = make_tuple(height/2,width/2);
    walls[key] = name_symbol; 
}

void Room::display_room_grid(){
    for(int x = 0; x < height; x++ ){
        for(int y =0; y < width; y++){
            auto key = make_tuple(x,y);
            cout << walls[key] << " "; 
        }
        cout << endl;
    }
}


