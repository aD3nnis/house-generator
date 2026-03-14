#ifndef LIVINGROOM_H
#define LIVINGROOM_H
#include <iostream>
using namespace std;

#include "Room.h"


class Livingroom : public Room{
    private: 
    float livingroom_size;
    int height;
    int width;

    public: 
        float get_size() const override;
        int get_width(){
            return width;
        }
        int get_height(){
            return height;
        }
        void set_width(int w){
            width = w;
        }
        void set_height(int h){
            height = h;
        }

         // my formula for room size: x = (100) / (b*r1 + a*r2 + r3 + 1)
        void set_livingroom_size(float bedrooms, float bed_size, float bathrooms, float bath_size, float kit_size){
            float denominator = (bedrooms * bed_size) + (bathrooms * bath_size) + kit_size + 1.0f;
            float x = (100.0f) / denominator;
            livingroom_size = x;
        }
        float set_dimensions(float percent, float totalSqft){
            return (percent / 100.0f) * totalSqft;   
        }
};
#endif