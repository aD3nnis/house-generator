#ifndef HOUSE_H 
#include <iostream>
#define HOUSE_H
using namespace std;

#include "Livingroom.h"
#include "Bedroom.h"
#include "Bathroom.h"
#include "Kitchen.h"
#include "Room.h"

class House{
    private: 
    Livingroom livingroom;
    vector<Bedroom> bedroom;    // should i have a list?
    vector<Bathroom> bathroom;  // should i have a list?
    Kitchen kitchen;
    float livingPercent;
    float totalBedroomPercent;
    float totalBathroomPercent;
    float kitchenPercent;

    vector<float> bedroomPercents;
    vector<float> bathroomPercents;

    public: 
    void set_bedroom_count(int bed_count){
        bedroom.resize(bed_count);
    }
    void set_bathroom_count(int bath_count){
        bathroom.resize(bath_count);
    }
    // percent of space they take up
    void set_room_percentages();

    void display(){
        // maybe
    }
    float get_living_percent(){
        return livingPercent;
    }
    float get_total_bedroom_percent(){
        return totalBedroomPercent;
    }
    float get_total_bathroom_percent(){
        return totalBathroomPercent;
    }
    float get_kitchen_percent(){
        return kitchenPercent;
    }
    Livingroom& get_livingroom() { return livingroom; }
    Bedroom& get_bedroom(int i){return bedroom.at(i);}
    vector<Bedroom>& get_bedrooms(){return bedroom;}
    Bathroom& get_bathroom(int i){return bathroom.at(i);}
    Kitchen& get_kitchen(){return kitchen; }

    int get_bedroom_count(){return bedroom.size();}
    int get_bathroom_count(){return bathroom.size();}
    int get_master_room(vector<float> room_percents, int master_num = 0);

    void set_bedroom_percents(vector<float> roomPercents);
    void set_bathroom_percents(vector<float> roomPercents);
    
    vector<float> get_bedroom_percents();
    vector<float> get_bathroom_percents();

    void create_rooms(House &house1, LayoutGenerator &layout_gen, int totalSqft);
};
#endif