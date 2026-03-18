#include "../../include/models/House.h"

// percent of space they take up
void House::set_room_percentages() {
  livingPercent = livingroom.get_default_size_ratio();
  totalBedroomPercent = bedroom.size() * Bedroom().get_default_size_ratio() *
                        livingroom.get_default_size_ratio();
  totalBathroomPercent = bathroom.size() * Bathroom().get_default_size_ratio() *
                         livingroom.get_default_size_ratio();
  kitchenPercent =
      kitchen.get_default_size_ratio() * livingroom.get_default_size_ratio();
}
int House::get_master_room(vector<float> room_percents, int master_num) {
  for (int i = 1; i < (int)room_percents.size(); i++) {
    if (room_percents[i] > room_percents[master_num]) {
      master_num = i;
    }
  }
  return master_num;
}
void House::set_bedroom_percents(vector<float> roomPercents) {
  bedroomPercents = roomPercents;
}
void House::set_bathroom_percents(vector<float> roomPercents) {
  bathroomPercents = roomPercents;
}
vector<float> House::get_bedroom_percents() { return bedroomPercents; }
vector<float> House::get_bathroom_percents() { return bathroomPercents; }
void House::create_rooms(House &house1, LayoutGenerator &layout_gen,
                         int totalSqft) {
  house1.get_livingroom().set_room_sqft(house1.get_living_percent(), totalSqft);
  house1.get_livingroom().update_dimensions(layout_gen);
  house1.get_livingroom().make_walls_of_room();
  house1.get_livingroom().place_name_in_room();

  house1.get_kitchen().set_room_sqft(house1.get_kitchen_percent(), totalSqft);
  house1.get_kitchen().update_dimensions(layout_gen);
  house1.get_kitchen().make_walls_of_room();
  house1.get_kitchen().place_name_in_room();

  for (int i = 0; i < house1.get_bedroom_count(); i++) {
    house1.get_bedroom(i).set_room_sqft(house1.get_bedroom_percents()[i],
                                        totalSqft);
    house1.get_bedroom(i).update_dimensions(layout_gen);
    house1.get_bedroom(i).make_walls_of_room();
    house1.get_bedroom(i).place_name_in_room();
  }

  for (int i = 0; i < house1.get_bathroom_count(); i++) {
    house1.get_bathroom(i).set_room_sqft(house1.get_bathroom_percents()[i],
                                         totalSqft);
    house1.get_bathroom(i).update_dimensions(layout_gen);
    house1.get_bathroom(i).make_walls_of_room();
    house1.get_bathroom(i).place_name_in_room();
  }
}