#include "../../include/systems/RuleValidator.h"

#include <queue>
#include <unordered_set>

namespace {

void addIssue(ValidationReport& report, const std::string& issue) {
    report.isValid = false;
    report.issues.push_back(issue);
}

bool roomHasNeighborType(const HouseLayout& layout, const Room& room, RoomType type) {
    for (int neighborId : room.adjacentRoomIds) {
        for (const Room& candidate : layout.rooms) {
            if (candidate.id == neighborId && candidate.type == type) {
                return true;
            }
        }
    }

    return false;
}

bool areAllRoomsReachable(const HouseLayout& layout) {
    if (layout.rooms.empty()) {
        return true;
    }

    std::queue<int> toVisit;
    std::unordered_set<int> visited;
    toVisit.push(layout.rooms.front().id);
    visited.insert(layout.rooms.front().id);

    while (!toVisit.empty()) {
        const int currentId = toVisit.front();
        toVisit.pop();

        for (const Room& room : layout.rooms) {
            if (room.id != currentId) {
                continue;
            }

            for (int neighborId : room.adjacentRoomIds) {
                if (visited.insert(neighborId).second) {
                    toVisit.push(neighborId);
                }
            }
        }
    }

    return visited.size() == layout.rooms.size();
}

} // namespace

ValidationReport RuleValidator::validate(const HouseLayout& layout) const {
    ValidationReport report;

    const std::vector<const Room*> bedrooms = layout.findAll(RoomType::Bedroom);
    const std::vector<const Room*> bathrooms = layout.findAll(RoomType::Bathroom);
    const Room* living = layout.findFirst(RoomType::LivingRoom);
    const Room* kitchen = layout.findFirst(RoomType::Kitchen);
    const Room* hallway = layout.findFirst(RoomType::Hallway);

    if (static_cast<int>(bedrooms.size()) >= 2 && hallway == nullptr) {
        addIssue(report, "A hallway is required when the house has 2 or more bedrooms.");
    }

    for (std::size_t i = 0; i < layout.rooms.size(); ++i) {
        for (std::size_t j = i + 1; j < layout.rooms.size(); ++j) {
            if (roomsOverlap(layout.rooms[i], layout.rooms[j])) {
                addIssue(
                    report,
                    layout.rooms[i].name + " overlaps " + layout.rooms[j].name + "."
                );
            }
        }
    }

    if (living == nullptr) {
        addIssue(report, "The layout is missing a living room.");
    }

    if (kitchen == nullptr) {
        addIssue(report, "The layout is missing a kitchen.");
    }

    if (living != nullptr && kitchen != nullptr) {
        const bool kitchenConnected =
            roomsAreAdjacent(*kitchen, *living) || (hallway != nullptr && roomsAreAdjacent(*kitchen, *hallway));
        if (!kitchenConnected) {
            addIssue(report, "The kitchen must touch the living room or the hallway.");
        }
    }

    if (hallway != nullptr && living != nullptr && !roomsAreAdjacent(*living, *hallway)) {
        addIssue(report, "The living room should connect to the hallway.");
    }

    for (const Room* bedroom : bedrooms) {
        if (kitchen != nullptr && roomsAreAdjacent(*bedroom, *kitchen)) {
            addIssue(report, bedroom->name + " should not share a wall with the kitchen.");
        }

        if (bedroom->area() < 60) {
            addIssue(report, bedroom->name + " is below the 60 sqft minimum.");
        }

        const float ratio =
            static_cast<float>(std::max(bedroom->width, bedroom->height)) /
            static_cast<float>(std::max(1, std::min(bedroom->width, bedroom->height)));
        if (ratio > 3.0f) {
            addIssue(report, bedroom->name + " exceeds the 3:1 aspect ratio limit.");
        }
    }

    bool commonBathroomTouchesHallway = hallway == nullptr;
    for (const Room* bathroom : bathrooms) {
        if (bathroom->area() < 40) {
            addIssue(report, bathroom->name + " is below the 40 sqft minimum.");
        }

        const bool touchesHallway = hallway != nullptr && roomsAreAdjacent(*bathroom, *hallway);
        if (!bathroom->isEnsuite && touchesHallway) {
            commonBathroomTouchesHallway = true;
        }
    }

    if (!commonBathroomTouchesHallway) {
        addIssue(report, "At least one common bathroom should connect to the hallway.");
    }

    if (hallway != nullptr && std::min(hallway->width, hallway->height) < 4) {
        addIssue(report, "The hallway must be at least 4 feet wide.");
    }

    if (!areAllRoomsReachable(layout)) {
        addIssue(report, "The placed rooms are not fully connected.");
    }

    return report;
}
