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

    int get_bedroom_count(){return bedroom.size();}
    int get_bathroom_count(){return bathroom.size();}
};
#endif