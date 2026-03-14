#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "../../include/systems/LayoutOutput.h"

class LayoutGenerator {
    private: 
        const float MIN_ROOM_VARIATION = 0.85f;
        const float MAX_ROOM_VARIATION = 1.25f;
    public:
        float get_min_room_variation(){
            return MIN_ROOM_VARIATION;
        }
        float get_max_room_variation(){
            return MAX_ROOM_VARIATION;
        }
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
};

