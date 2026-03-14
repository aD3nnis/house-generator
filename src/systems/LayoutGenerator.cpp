#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
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
    cout << "in function: middle: " << width << " height: " << height << endl;
    // adjust until aspect ratio <= 3:1
    while (((float)height / width > 3.0f) || ((float)width / height > 3.0f)) {
        cout << " in while width: " << width << "height: " << height << endl;
        width++;
        height = (int)(sqft / width);
        if (height < 1) { height = 1; break; }
    }
}


