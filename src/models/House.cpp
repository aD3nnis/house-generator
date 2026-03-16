#include "../../include/models/House.h"

    // percent of space they take up
void House::set_room_percentages(){
        livingPercent = livingroom.get_default_size_ratio();
        totalBedroomPercent = bedroom.size() * Bedroom().get_default_size_ratio() * livingroom.get_default_size_ratio();
        totalBathroomPercent = bathroom.size() * Bathroom().get_default_size_ratio() * livingroom.get_default_size_ratio();
        kitchenPercent = kitchen.get_default_size_ratio() * livingroom.get_default_size_ratio();
    }
int House::get_master_room(vector<float> room_percents, int master_num){
    for (int i = 1; i < (int)room_percents.size(); i++)
    {
        if (room_percents[i] > room_percents[master_num])
        {
            master_num = i;
        }
    }
    return master_num;
}
void House::set_bedroom_percents(vector<float> roomPercents){
    bedroomPercents = roomPercents;

}
void House::set_bathroom_percents(vector<float> roomPercents){
    bathroomPercents = roomPercents;
}
vector<float> House::get_bedroom_percents(){
    return bedroomPercents;
}
vector<float> House::get_bathroom_percents(){
    return bathroomPercents;
}
