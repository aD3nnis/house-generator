#include "../../include/models/House.h"

    // percent of space they take up
void House::set_room_percentages(){
        livingPercent = livingroom.get_default_size_ratio();
        totalBedroomPercent = bedroom.size() * Bedroom().get_default_size_ratio() * livingroom.get_default_size_ratio();
        totalBathroomPercent = bathroom.size() * Bathroom().get_default_size_ratio() * livingroom.get_default_size_ratio();
        kitchenPercent = kitchen.get_default_size_ratio() * livingroom.get_default_size_ratio();
    }