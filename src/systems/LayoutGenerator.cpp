#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#include "../../include/systems/LayoutOutput.h"
#include "../../include/systems/LayoutGenerator.h"


float LayoutGenerator::get_min_room_variation(){
    return MIN_ROOM_VARIATION;
}
float LayoutGenerator::get_max_room_variation(){
    return MAX_ROOM_VARIATION;
}
// Convert sqft to dimensions with max 3:1 aspect ratio
void LayoutGenerator::calcDimensions(float &sqft, int& width, int& height) {
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
vector<float> LayoutGenerator::distributePercent(int room_count, float totalPercent, LayoutGenerator &layout_gen){
    
        vector<float> percents;
    if (room_count <= 0)
        return percents;

    vector<float> weights;
    float totalWeight = 0.0f;

    for (int i = 0; i < room_count; i++)
    {
        float weight = randomWeight(layout_gen);
        weights.push_back(weight);
        totalWeight += weight; // calculate the total weight of the rooms
    }

    for (float weight : weights)
    {
        percents.push_back((weight / totalWeight) * totalPercent); // calculate the percentage of each room as a share of the total percentage
    }

    return percents;
}

float LayoutGenerator::randomWeight(LayoutGenerator &layout_gen)
    {
        float t = (float)rand() / (float)RAND_MAX;                                                                                    // random number between 0 and 1
        return layout_gen.get_min_room_variation() + t * (layout_gen.get_max_room_variation() - layout_gen.get_min_room_variation()); // random weight between MIN_ROOM_VARIATION and MAX_ROOM_VARIATION
    };
