#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

#pragma once
#ifndef LAYOUT_GENERATOR_H
#define LAYOUT_GENERATOR_H
#include "LayoutOutput.h"

class LayoutGenerator {
    private: 
        const float MIN_ROOM_VARIATION = 0.85f;
        const float MAX_ROOM_VARIATION = 1.25f;
    public:
        float get_min_room_variation();
        float get_max_room_variation();
        // Convert sqft to dimensions with max 3:1 aspect ratio
        void calcDimensions(float &sqft, int& width, int& height);
        vector<float> distributePercent(int roomCount, float totalPercent, LayoutGenerator &layout_gen);
        float randomWeight(LayoutGenerator &layout_gen);
};

#endif