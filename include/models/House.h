#ifndef HOUSE_H
#define HOUSE_H

#include <algorithm>
#include <vector>

#include "LayoutRequest.h"
#include "Room.h"

struct HouseLayout {
    LayoutRequest request {};
    std::vector<Room> rooms;
    bool hasHallway = false;
    float hallwayPercent = 0.0f;

    int minX() const {
        if (rooms.empty()) return 0;

        int value = rooms.front().position.x;
        for (const Room& room : rooms) {
            value = std::min(value, room.position.x);
        }
        return value;
    }

    int minY() const {
        if (rooms.empty()) return 0;

        int value = rooms.front().position.y;
        for (const Room& room : rooms) {
            value = std::min(value, room.position.y);
        }
        return value;
    }

    int maxRight() const {
        if (rooms.empty()) return 0;

        int value = rooms.front().right();
        for (const Room& room : rooms) {
            value = std::max(value, room.right());
        }
        return value;
    }

    int maxBottom() const {
        if (rooms.empty()) return 0;

        int value = rooms.front().bottom();
        for (const Room& room : rooms) {
            value = std::max(value, room.bottom());
        }
        return value;
    }

    int width() const {
        return maxRight() - minX();
    }

    int height() const {
        return maxBottom() - minY();
    }

    void normalizeToOrigin() {
        const int offsetX = minX();
        const int offsetY = minY();

        for (Room& room : rooms) {
            room.position.x -= offsetX;
            room.position.y -= offsetY;
        }
    }

    Room* findFirst(RoomType type) {
        for (Room& room : rooms) {
            if (room.type == type) {
                return &room;
            }
        }
        return nullptr;
    }

    const Room* findFirst(RoomType type) const {
        for (const Room& room : rooms) {
            if (room.type == type) {
                return &room;
            }
        }
        return nullptr;
    }

    std::vector<Room*> findAll(RoomType type) {
        std::vector<Room*> matches;
        for (Room& room : rooms) {
            if (room.type == type) {
                matches.push_back(&room);
            }
        }
        return matches;
    }

    std::vector<const Room*> findAll(RoomType type) const {
        std::vector<const Room*> matches;
        for (const Room& room : rooms) {
            if (room.type == type) {
                matches.push_back(&room);
            }
        }
        return matches;
    }
};

inline bool roomsOverlap(const Room& first, const Room& second) {
    return first.position.x < second.right()
        && first.right() > second.position.x
        && first.position.y < second.bottom()
        && first.bottom() > second.position.y;
}

inline int sharedWallLength(const Room& first, const Room& second) {
    const bool touchesVertically =
        first.right() == second.position.x || second.right() == first.position.x;
    const bool touchesHorizontally =
        first.bottom() == second.position.y || second.bottom() == first.position.y;

    if (touchesVertically) {
        const int overlapTop = std::max(first.position.y, second.position.y);
        const int overlapBottom = std::min(first.bottom(), second.bottom());
        return std::max(0, overlapBottom - overlapTop);
    }

    if (touchesHorizontally) {
        const int overlapLeft = std::max(first.position.x, second.position.x);
        const int overlapRight = std::min(first.right(), second.right());
        return std::max(0, overlapRight - overlapLeft);
    }

    return 0;
}

inline bool roomsAreAdjacent(const Room& first, const Room& second) {
    return sharedWallLength(first, second) > 0;
}

inline void refreshAdjacency(HouseLayout& layout) {
    for (Room& room : layout.rooms) {
        room.adjacentRoomIds.clear();
    }

    for (std::size_t i = 0; i < layout.rooms.size(); ++i) {
        for (std::size_t j = i + 1; j < layout.rooms.size(); ++j) {
            if (roomsAreAdjacent(layout.rooms[i], layout.rooms[j])) {
                layout.rooms[i].adjacentRoomIds.push_back(layout.rooms[j].id);
                layout.rooms[j].adjacentRoomIds.push_back(layout.rooms[i].id);
            }
        }
    }
}

#endif
