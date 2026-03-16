#ifndef LAYOUT_GENERATOR_H
#define LAYOUT_GENERATOR_H

#include <vector>

#include "../models/House.h"

class LayoutGenerator {
public:
    LayoutGenerator();

    std::vector<Room> buildRoomProgram(const LayoutRequest& request) const;
    HouseLayout placeRooms(const LayoutRequest& request, std::vector<Room> rooms) const;
    HouseLayout generateLayout(const LayoutRequest& request) const;
};

#endif
