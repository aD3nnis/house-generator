#include "../include/systems/LayoutOutput.h"
#include "systems/LayoutGenerator.cpp"
#include "../include/models/Room.h"
#include "../include/models/Bathroom.h"
#include "../include/models/Bedroom.h"
#include "../include/models/Kitchen.h"
#include "../include/models/Livingroom.h"
#include "../include/models/Grid.h"
#include "../include/models/Position.h"
#include "../include/models/House.h"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    House house1;
    LayoutGenerator layout_gen;
    Grid grid;
    Position position;
    srand((unsigned)time(nullptr));

    int bedrooms, bathrooms, totalSqft;

    std::cout << "\n=== House Layout Math Calculator ===\n\n";
    std::cout << "Enter number of bedrooms  (1-6): ";
    std::cin >> bedrooms;
    std::cout << "Enter number of bathrooms (1-4): ";
    std::cin >> bathrooms;
    std::cout << "Enter total square footage (500 - 2000):";
    std::cin >> totalSqft;

    house1.set_bedroom_count(bedrooms);
    house1.set_bathroom_count(bathrooms);

    // I used temporary classes because the default size ratio is the same for each
    house1.get_livingroom().set_livingroom_size(house1.get_bedroom_count(), Bedroom().get_default_size_ratio(), house1.get_bathroom_count(), Bathroom().get_default_size_ratio(), Kitchen().get_default_size_ratio());

    //  Assign percentages
    house1.set_room_percentages();

    // random weight for the room
    house1.set_bedroom_percents(layout_gen.distributePercent(house1.get_bedroom_count(), house1.get_total_bedroom_percent(), layout_gen));
    house1.set_bathroom_percents(layout_gen.distributePercent(house1.get_bathroom_count(), house1.get_total_bathroom_percent(), layout_gen));
    
    cout << "livingroom: " << endl;
    house1.get_livingroom().set_room_sqft(house1.get_living_percent(), totalSqft);
    house1.get_livingroom().update_dimensions(layout_gen);
    house1.get_livingroom().make_walls_of_room();
    house1.get_livingroom().place_name_in_room();
    house1.get_livingroom().display_room_grid();

    cout << "kitchen: " << endl;
    house1.get_kitchen().set_room_sqft(house1.get_kitchen_percent(), totalSqft);
    house1.get_kitchen().update_dimensions(layout_gen);
    house1.get_kitchen().make_walls_of_room();
    house1.get_kitchen().place_name_in_room();
    house1.get_kitchen().display_room_grid();

    for (int i = 0; i < house1.get_bedroom_count(); i++){
        cout << "bed[" << i + 1<<"]" << endl;
        house1.get_bedroom(i).set_room_sqft( house1.get_bedroom_percents()[i], totalSqft);
        house1.get_bedroom(i).update_dimensions(layout_gen);
        house1.get_bedroom(i).make_walls_of_room();
        house1.get_bedroom(i).place_name_in_room();
        house1.get_bedroom(i).display_room_grid();
    }

    for (int i = 0; i < house1.get_bathroom_count(); i++){
        cout << "bath[" << i + 1<<"]" << endl;
        house1.get_bathroom(i).set_room_sqft(house1.get_bathroom_percents()[i], totalSqft);
        house1.get_bathroom(i).update_dimensions(layout_gen);
        house1.get_bathroom(i).make_walls_of_room();
        house1.get_bathroom(i).place_name_in_room();
        house1.get_bathroom(i).display_room_grid();
    }

    position.place_livingroom(grid, house1);

    grid.display_grid();



    vector<RoomResult> rooms;
    // for output

    //  Convert to sqft and dimensions
    auto makeRoom = [&](std::string name, float percent) -> RoomResult { // pass by reference to the function
        RoomResult r;                                                    // create a new room result object
        r.name = name;                                                   // set the name of the room
        r.percent = percent;                                             // set the percentage of the room
        r.sqft = (percent / 100.0f) * totalSqft;                         // set the sqft of the room
        layout_gen.calcDimensions(r.sqft, r.width, r.height);            // calculate the dimensions of the room
        return r;
    };

    // dont take string take Object
    rooms.push_back(makeRoom("Living Room", house1.get_living_percent()));
    rooms.push_back(makeRoom("Kitchen", house1.get_kitchen_percent()));

    for (int i = 1; i <= house1.get_bedroom_count(); i++)
    {
        bool isMaster = (i - 1 == house1.get_master_room(house1.get_bedroom_percents()));
        std::string name = "Bedroom " + std::to_string(i);
        if (isMaster)
            name += " (Master)";
        rooms.push_back(makeRoom(name,  house1.get_bedroom_percents()[i - 1]));
    }

    for (int i = 1; i <= house1.get_bathroom_count(); i++)
    {
        bool isEnsuite = (house1.get_bathroom_count() > 1) && (i - 1 == house1.get_master_room(house1.get_bathroom_percents()));
        std::string name = "Bathroom " + std::to_string(i);
        if (isEnsuite)
            name += " (Ensuite)";
        float percent = house1.get_bathroom_percents()[i - 1];

        rooms.push_back(makeRoom(name, percent));
    }

    printLayoutReport(rooms, totalSqft);

    return 0;
}
