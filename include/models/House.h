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
    vector<Bedroom> bedrooms;    // should i have a list?
    vector<Bathroom> bathrooms;  // should i have a list?
    Kitchen kitchen;
    float livingPercent;
    float totalBedroomPercent;
    float totalBathroomPercent;
    float kitchenPercent;

    public: 
    void set_bedroom_count(int bed_count){
        bedrooms.resize(bed_count);
    }
    void set_bathroom_count(int bath_count){
        bathrooms.resize(bath_count);
    }
    // percent of space they take up
    void set_room_percentages(){
        livingPercent = livingroom.get_default_size_ratio();
        totalBedroomPercent = bedrooms.size() * Bedroom().get_default_size_ratio() * livingroom.get_default_size_ratio();
        totalBathroomPercent = bathrooms.size() * Bathroom().get_default_size_ratio() * livingroom.get_default_size_ratio();
        kitchenPercent = kitchen.get_default_size_ratio() * livingroom.get_default_size_ratio();
    }
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
};
#endif