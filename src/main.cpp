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
    Kitchen kit("kit");
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

    vector<Bedroom> beds;  
    vector<Bathroom> baths; 

    house1.set_bedroom_count(bedrooms);
    house1.set_bathroom_count(bathrooms);
    beds.resize(bedrooms);   // resize is vector function
    baths.resize(bathrooms); // resize is vector function
    // use to be that above code needs to be before code below because vector needs a side to call from bed in index
    // but i can use temporary classes because the default size ratio is the same for each
    
    house1.get_livingroom().set_livingroom_size(bedrooms, Bedroom().get_default_size_ratio(), bathrooms, Bathroom().get_default_size_ratio(), kit.get_default_size_ratio());
    //  Assign percentages
    house1.set_room_percentages();
    //  Convert to sqft and dimensions
    auto makeRoom = [&](std::string name, float percent) -> RoomResult { // pass by reference to the function
        RoomResult r;                                                    // create a new room result object
        r.name = name;                                                   // set the name of the room
        r.percent = percent;                                             // set the percentage of the room
        r.sqft = (percent / 100.0f) * totalSqft;                         // set the sqft of the room
        layout_gen.calcDimensions(r.sqft, r.width, r.height);            // calculate the dimensions of the room
        return r;
    };
    // random weight for the room
    auto randomWeight = [&layout_gen]() -> float
    {
        float t = (float)rand() / (float)RAND_MAX;                                                                                    // random number between 0 and 1
        return layout_gen.get_min_room_variation() + t * (layout_gen.get_max_room_variation() - layout_gen.get_min_room_variation()); // random weight between MIN_ROOM_VARIATION and MAX_ROOM_VARIATION
    };

    auto distributePercent = [&](int count, float totalPercent) -> vector<float>
    {
        vector<float> percents;
        if (count <= 0)
            return percents;

        vector<float> weights;
        float totalWeight = 0.0f;

        for (int i = 0; i < count; i++)
        {
            float weight = randomWeight();
            weights.push_back(weight);
            totalWeight += weight; // calculate the total weight of the rooms
        }

        for (float weight : weights)
        {
            percents.push_back((weight / totalWeight) * totalPercent); // calculate the percentage of each room as a share of the total percentage
        }

        return percents;
    };

    vector<float> bedroomPercents = distributePercent(bedrooms, house1.get_total_bedroom_percent());
    vector<float> bathroomPercents = distributePercent(bathrooms, house1.get_total_bathroom_percent());

    int masterBedroomIndex = 0;
    // find the master bedroom index
    for (int i = 1; i < (int)bedroomPercents.size(); i++)
    {
        if (bedroomPercents[i] > bedroomPercents[masterBedroomIndex])
        {
            masterBedroomIndex = i;
        }
    }

    int ensuiteBathroomIndex = 0;
    // find the ensuite bathroom index
    for (int i = 1; i < (int)bathroomPercents.size(); i++)
    {
        if (bathroomPercents[i] > bathroomPercents[ensuiteBathroomIndex])
        {
            ensuiteBathroomIndex = i;
        }
    }

    vector<RoomResult> rooms;
    // for output

    // dont take string take Object
    rooms.push_back(makeRoom("Living Room", house1.get_living_percent()));
    rooms.push_back(makeRoom("Kitchen", house1.get_kitchen_percent()));
    house1.get_livingroom().set_room_sqft(house1.get_living_percent(), totalSqft);
    house1.get_livingroom().update_dimensions(layout_gen);
    position.place_livingroom(grid, house1.get_livingroom());
    grid.display_grid();

    for (int i = 1; i <= bedrooms; i++)
    {
        bool isMaster = (i - 1 == masterBedroomIndex);
        std::string name = "Bedroom " + std::to_string(i);
        if (isMaster)
            name += " (Master)";
        float percent = bedroomPercents[i - 1];
        house1.get_bedroom(i-1).set_room_sqft(percent, totalSqft);
        house1.get_bedroom(i-1).update_dimensions(layout_gen);
        rooms.push_back(makeRoom(name, percent));
    }
    house1.get_bedroom(0).make_walls_of_room();
    house1.get_bedroom(0).display_room_grid();

    for (int i = 1; i <= bathrooms; i++)
    {
        bool isEnsuite = (bathrooms > 1) && (i - 1 == ensuiteBathroomIndex);
        std::string name = "Bathroom " + std::to_string(i);
        if (isEnsuite)
            name += " (Ensuite)";
        float percent = bathroomPercents[i - 1];
        rooms.push_back(makeRoom(name, percent));
    }

    printLayoutReport(rooms, totalSqft);

    return 0;
}
