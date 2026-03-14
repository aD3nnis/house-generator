#include "../include/systems/LayoutOutput.h"
#include "systems/LayoutGenerator.cpp"
#include "../include/models/Room.h"
#include "../include/models/Bathroom.h"
#include "../include/models/Bedroom.h"
#include "../include/models/Kitchen.h"
#include "../include/models/Livingroom.h"
#include <iomanip>
#include <iostream>
using namespace std;

int main(){
    Bedroom bed;
    Bathroom bath;
    Kitchen kit;
    LayoutGenerator layout1;
    srand((unsigned)time(nullptr));

    int bedrooms, bathrooms, totalSqft;

    std::cout << "\n=== House Layout Math Calculator ===\n\n";
    std::cout << "Enter number of bedrooms  (1-6): "; std::cin >> bedrooms;
    std::cout << "Enter number of bathrooms (1-4): "; std::cin >> bathrooms;
    std::cout << "Enter total square footage:      "; std::cin >> totalSqft;

    // my formula for room size: x = (100) / (b*r1 + a*r2 + r3 + 1)
    float denominator = (bedrooms * bed.get_size()) + (bathrooms * bath.get_size()) + kit.get_size() + 1.0f;
    float x = (100.0f) / denominator;

    //  Assign percentages
    float pLiving   = x;
    float totalBedroomPercent = bedrooms * bed.get_size() * x;
    float totalBathroomPercent = bathrooms * bath.get_size() * x;
    float pKitchen  = kit.get_size()  * x;

    //  Convert to sqft and dimensions
    auto makeRoom = [&](std::string name, float percent) -> RoomResult { //pass by reference to the function
        RoomResult r; //create a new room result object
        r.name    = name; //set the name of the room
        r.percent = percent; //set the percentage of the room
        r.sqft    = (percent / 100.0f) * totalSqft; //set the sqft of the room
        layout1.calcDimensions(r.sqft, r.width, r.height); //calculate the dimensions of the room
        return r;
    };
    // random weight for the room
    auto randomWeight = [&layout1]() -> float {
        float t = (float)rand() / (float)RAND_MAX; //random number between 0 and 1
        return layout1.get_min_room_variation() + t * (layout1.get_max_room_variation() - layout1.get_min_room_variation()); //random weight between MIN_ROOM_VARIATION and MAX_ROOM_VARIATION
    };

    auto distributePercent = [&](int count, float totalPercent) -> std::vector<float> {
        std::vector<float> percents;
        if (count <= 0) return percents;

        std::vector<float> weights;
        float totalWeight = 0.0f;

        for (int i = 0; i < count; i++) {
            float weight = randomWeight();
            weights.push_back(weight);
            totalWeight += weight; //calculate the total weight of the rooms
        }

        for (float weight : weights) {
            percents.push_back((weight / totalWeight) * totalPercent); //calculate the percentage of each room as a share of the total percentage
        }

        return percents;
    };

    std::vector<float> bedroomPercents = distributePercent(bedrooms, totalBedroomPercent);
    std::vector<float> bathroomPercents = distributePercent(bathrooms, totalBathroomPercent);

    int masterBedroomIndex = 0; 
    // find the master bedroom index
    for (int i = 1; i < (int)bedroomPercents.size(); i++) {
        if (bedroomPercents[i] > bedroomPercents[masterBedroomIndex]) {
            masterBedroomIndex = i;
        }
    }

    int ensuiteBathroomIndex = 0;
    // find the ensuite bathroom index
    for (int i = 1; i < (int)bathroomPercents.size(); i++) {
        if (bathroomPercents[i] > bathroomPercents[ensuiteBathroomIndex]) {
            ensuiteBathroomIndex = i;
        }
    }

    std::vector<RoomResult> rooms;
    // for output

    rooms.push_back(makeRoom("Living Room", pLiving));
    rooms.push_back(makeRoom("Kitchen", pKitchen));

    for (int i = 1; i <= bedrooms; i++) {
        bool isMaster = (i - 1 == masterBedroomIndex);
        std::string name = "Bedroom " + std::to_string(i);
        if (isMaster) name += " (Master)";
        float percent = bedroomPercents[i - 1];
        rooms.push_back(makeRoom(name, percent));
    }

    for (int i = 1; i <= bathrooms; i++) {
        bool isEnsuite = (bathrooms > 1) && (i - 1 == ensuiteBathroomIndex);
        std::string name = "Bathroom " + std::to_string(i);
        if (isEnsuite) name += " (Ensuite)";
        float percent = bathroomPercents[i - 1];
        rooms.push_back(makeRoom(name, percent));
    }

    printLayoutReport(rooms, totalSqft);

    return 0;
}
