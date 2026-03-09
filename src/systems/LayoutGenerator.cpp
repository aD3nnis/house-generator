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


    // my formula for room sise: x = (100 - H) / (b*r1 + a*r2 + r3 + 1)
    float denominator = (bedrooms * R_BEDROOM) + (bathrooms * R_BATHROOM) + R_KITCHEN + 1.0f;
    float x = (100.0f - H) / denominator;

    //  Assign percentages
    float pLiving   = x;
    float pBedroom  = R_BEDROOM  * x;
    float pBathroom = R_BATHROOM * x;
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

    std::vector<RoomResult> rooms;
    // for output
    if (hasHallway) {
        rooms.push_back(makeRoom("Hallway", H));
    }

    rooms.push_back(makeRoom("Living Room", pLiving));
    rooms.push_back(makeRoom("Kitchen", pKitchen));

    for (int i = 1; i <= bedrooms; i++) {
        std::string name = (i == 1) ? "Bedroom 1 (Master)" : "Bedroom " + std::to_string(i);
        rooms.push_back(makeRoom(name, pBedroom));
    }

    for (int i = 1; i <= bathrooms; i++) {
        std::string name = (bathrooms >= 2 && i == 1) ? "Bathroom 1 (Ensuite)" : "Bathroom " + std::to_string(i);
        rooms.push_back(makeRoom(name, pBathroom));
    }

    printLayoutReport(rooms, hasHallway, totalSqft);

    return 0;
}