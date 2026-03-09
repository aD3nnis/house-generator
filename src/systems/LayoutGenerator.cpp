#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "LayoutOutput.h"

// Ratios that I picked relative to living room
const float R_BEDROOM  = 0.7f;
const float R_BATHROOM = 0.4f;
const float R_KITCHEN  = 0.8f;
const float MIN_ROOM_VARIATION = 0.85f;
const float MAX_ROOM_VARIATION = 1.25f;

// Convert sqft to dimensions with max 3:1 aspect ratio
void calcDimensions(float sqft, int& width, int& height) {
    width  = (int)std::sqrt(sqft);
    if (width < 1) width = 1;
    height = (int)(sqft / width);
    if (height < 1) height = 1;

    // adjust until aspect ratio <= 3:1
    while (((float)height / width > 3.0f) || ((float)width / height > 3.0f)) {
        width++;
        height = (int)(sqft / width);
        if (height < 1) { height = 1; break; }
    }
}

int main() {
    srand((unsigned)time(nullptr));

    int bedrooms, bathrooms, totalSqft;

    std::cout << "\n=== House Layout Math Calculator ===\n\n";
    std::cout << "Enter number of bedrooms  (1-6): "; std::cin >> bedrooms;
    std::cout << "Enter number of bathrooms (1-4): "; std::cin >> bathrooms;
    std::cout << "Enter total square footage:       "; std::cin >> totalSqft;

    
    float H; // hallway percentage which can have decimals
    bool hasHallway; // if hallway is present true or false

    // only matters for 1 bedroom because hallway is required for 2+ bedrooms
    if (bedrooms == 1) {
        // random 0-20, if 0 no hallway
        int roll = rand() % 21;  // 0 to 20
        H = (float)roll;
        hasHallway = (roll != 0);
    } else { // more than 1 bedroom
        // random 5-20, always has hallway
        H = (float)(rand() % 16 + 5);  // 5 to 20
        hasHallway = true;
    }
    // my formula for room size: x = (100 - H) / (b*r1 + a*r2 + r3 + 1)
    float denominator = (bedrooms * R_BEDROOM) + (bathrooms * R_BATHROOM) + R_KITCHEN + 1.0f;
    float x = (100.0f - H) / denominator;

    //  Assign percentages
    float pLiving   = x;
    float totalBedroomPercent = bedrooms * R_BEDROOM * x;
    float totalBathroomPercent = bathrooms * R_BATHROOM * x;
    float pKitchen  = R_KITCHEN  * x;

    //  Convert to sqft and dimensions
    auto makeRoom = [&](std::string name, float percent) -> RoomResult { //pass by reference to the function
        RoomResult r; //create a new room result object
        r.name    = name; //set the name of the room
        r.percent = percent; //set the percentage of the room
        r.sqft    = (percent / 100.0f) * totalSqft; //set the sqft of the room
        calcDimensions(r.sqft, r.width, r.height); //calculate the dimensions of the room
        return r;
    };
    // random weight for the room
    auto randomWeight = []() -> float {
        float t = (float)rand() / (float)RAND_MAX; //random number between 0 and 1
        return MIN_ROOM_VARIATION + t * (MAX_ROOM_VARIATION - MIN_ROOM_VARIATION); //random weight between MIN_ROOM_VARIATION and MAX_ROOM_VARIATION
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
    if (hasHallway) {
        rooms.push_back(makeRoom("Hallway", H));
    }

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

    printLayoutReport(rooms, hasHallway, totalSqft);

    return 0;
}