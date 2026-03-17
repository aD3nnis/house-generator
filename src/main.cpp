#include "../include/models/Bathroom.h"
#include "../include/models/Bedroom.h"
#include "../include/models/Grid.h"
#include "../include/models/House.h"
#include "../include/models/Kitchen.h"
#include "../include/models/Livingroom.h"
#include "../include/models/Room.h"
#include "../include/systems/LayoutGenerator.h"
#include "../include/systems/LayoutOutput.h"
#include "../include/systems/Position.h"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int bedrooms = 0;
    int bathrooms = 0;
    int totalSqft = 0;

    cout << "\n\"...screw it, I'm gonna go build a house\" - Jack, AH \n";
    cout << "\n====== House Layout Generator ======\n\n";


  while (bedrooms > 4 || bedrooms < 1) {
    cout << "Enter number of bedrooms  (1-4): ";
    cin >> bedrooms;
  }
  while (bathrooms > 3 || bathrooms < 1) {
    cout << "Enter number of bathrooms (1-3): ";
    cin >> bathrooms;
  }
  while (totalSqft > 1000 || totalSqft < 500) {
    cout << "Enter total square footage (500 - 1000):";
    cin >> totalSqft;
  }
  char again = 'y';
  while (again == 'y' || again == 'Y') {
    House house1;
    LayoutGenerator layout_gen;
    Grid grid;
    Position position;
    srand((unsigned)time(nullptr));

    house1.set_bedroom_count(bedrooms);
    house1.set_bathroom_count(bathrooms);

    // I used temporary classes because the default size ratio is the same for
    // each
    house1.get_livingroom().set_livingroom_size(
        house1.get_bedroom_count(), Bedroom().get_default_size_ratio(),
        house1.get_bathroom_count(), Bathroom().get_default_size_ratio(),
        Kitchen().get_default_size_ratio());

    //  Assign percentages
    house1.set_room_percentages();

    // random weight for the room
    house1.set_bedroom_percents(layout_gen.distributePercent(
        house1.get_bedroom_count(), house1.get_total_bedroom_percent(),
        layout_gen));
    house1.set_bathroom_percents(layout_gen.distributePercent(
        house1.get_bathroom_count(), house1.get_total_bathroom_percent(),
        layout_gen));
    house1.create_rooms(house1, layout_gen, totalSqft);

    position.place_livingroom(grid, house1);
    position.check_if_side_taken(grid, house1.get_livingroom());
    vector<Room *> placed;
    placed.push_back(&house1.get_livingroom());

    vector<Room *> toPlace;
    toPlace.push_back(&house1.get_kitchen());
    for (int i = 0; i < house1.get_bedroom_count(); ++i)
      toPlace.push_back(&house1.get_bedroom(i));
    for (int i = 0; i < house1.get_bathroom_count(); ++i)
      toPlace.push_back(&house1.get_bathroom(i));

    position.place_rooms_random(grid, placed, toPlace);

    // output
    vector<RoomResult> rooms;

    //  Convert to sqft and dimensions
    auto makeRoom =
        [&](std::string name,
            float percent) -> RoomResult { // pass by reference to the function
      RoomResult r;                        // create a new room result object
      r.name = name;                       // set the name of the room
      r.percent = percent;                 // set the percentage of the room
      r.sqft = (percent / 100.0f) * totalSqft; // set the sqft of the room
      layout_gen.calcDimensions(
          r.sqft, r.width, r.height); // calculate the dimensions of the room
      return r;
    };

    // dont take string take Object
    rooms.push_back(makeRoom("Living Room", house1.get_living_percent()));
    rooms.push_back(makeRoom("Kitchen", house1.get_kitchen_percent()));

    for (int i = 1; i <= house1.get_bedroom_count(); i++) {
      bool isMaster =
          (i - 1 == house1.get_master_room(house1.get_bedroom_percents()));
      std::string name = "Bedroom " + std::to_string(i);
      if (isMaster)
        name += " (Master)";
      rooms.push_back(makeRoom(name, house1.get_bedroom_percents()[i - 1]));
    }

    for (int i = 1; i <= house1.get_bathroom_count(); i++) {
      bool isEnsuite =
          (house1.get_bathroom_count() > 1) &&
          (i - 1 == house1.get_master_room(house1.get_bathroom_percents()));
      std::string name = "Bathroom " + std::to_string(i);
      if (isEnsuite)
        name += " (Ensuite)";
      float percent = house1.get_bathroom_percents()[i - 1];

      rooms.push_back(makeRoom(name, percent));
    }

    printLayoutReport(rooms, totalSqft);

    grid.display_grid();

    std::cout << "Do you want to run the program again? (y/n): ";
    std::cin >> again;
  }

  return 0;
}
