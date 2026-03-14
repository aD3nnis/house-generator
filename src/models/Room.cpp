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

