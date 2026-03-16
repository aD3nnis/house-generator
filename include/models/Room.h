#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "Position.h"

enum class RoomType {
    LivingRoom,
    Kitchen,
    Bedroom,
    Bathroom,
    Hallway
};

inline std::string roomTypeToString(RoomType type) {
    switch (type) {
        case RoomType::LivingRoom: return "Living Room";
        case RoomType::Kitchen: return "Kitchen";
        case RoomType::Bedroom: return "Bed";
        case RoomType::Bathroom: return "Bath";
        case RoomType::Hallway: return "Hallway";
    }

    return "Unknown";
}

inline char roomTypeToSymbol(RoomType type) {
    switch (type) {
        case RoomType::LivingRoom: return 'L';
        case RoomType::Kitchen: return 'K';
        case RoomType::Bedroom: return 'B';
        case RoomType::Bathroom: return 'T';
        case RoomType::Hallway: return 'H';
    }

    return '?';
}

struct Room {
    int id = -1;
    RoomType type = RoomType::LivingRoom;
    std::string name;
    float percent = 0.0f;
    float sqft = 0.0f;
    int width = 0;
    int height = 0;
    Position position {};
    bool placed = false;
    bool isMaster = false;
    bool isEnsuite = false;
    std::vector<int> adjacentRoomIds;

    int right() const { return position.x + width; }
    int bottom() const { return position.y + height; }
    int area() const { return width * height; }
};

#endif
