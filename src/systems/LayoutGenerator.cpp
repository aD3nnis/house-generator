#include "../../include/systems/LayoutGenerator.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>
#include <vector>

// anything in this namespace can’t be used from other .cpp files
namespace {

const float R_BEDROOM = 0.7f;
const float R_BATHROOM = 0.4f;
const float R_KITCHEN = 0.8f;
const float MIN_ROOM_VARIATION = 0.85f;
const float MAX_ROOM_VARIATION = 1.25f;

// calculate the dimensions of a room
void calcDimensions(float sqft, int& width, int& height) {
    width = static_cast<int>(std::sqrt(sqft));
    if (width < 1) width = 1;

    height = static_cast<int>(sqft / width);
    if (height < 1) height = 1;

    while ((static_cast<float>(height) / width > 3.0f) ||
           (static_cast<float>(width) / height > 3.0f)) {
        ++width;
        height = static_cast<int>(sqft / width);
        if (height < 1) {
            height = 1;
            break;
        }
    }
}

// random weight for the room
float randomWeight() {
    const float t = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    return MIN_ROOM_VARIATION + t * (MAX_ROOM_VARIATION - MIN_ROOM_VARIATION);
}

std::vector<float> distributePercent(int count, float totalPercent) {
    std::vector<float> percents;
    if (count <= 0) {
        return percents;
    }

    std::vector<float> weights;
    float totalWeight = 0.0f;

    for (int i = 0; i < count; ++i) {
        const float weight = randomWeight();
        weights.push_back(weight);
        totalWeight += weight;
    }

    for (float weight : weights) {
        percents.push_back((weight / totalWeight) * totalPercent);
    }

    return percents;
}

// swap the orientation of a room
void swapOrientation(Room& room) {
    std::swap(room.width, room.height);
}

// prefer horizontal orientation for a room
void preferHorizontal(Room& room) {
    if (room.height > room.width) {
        swapOrientation(room);
    }
}

void preferVertical(Room& room) {
    if (room.width > room.height) {
        swapOrientation(room);
    }
}

void prepareHallway(Room& hallway) {
    preferHorizontal(hallway);

    if (hallway.height < 4) {
        hallway.height = 4;
        hallway.width = std::max(hallway.width, static_cast<int>(std::ceil(hallway.sqft / hallway.height)));
    }
}

Room makeRoom(int id, RoomType type, const std::string& name, float percent, int totalSqft) {
    Room room;
    room.id = id;
    room.type = type;
    room.name = name;
    room.percent = percent;
    room.sqft = (percent / 100.0f) * totalSqft;

    calcDimensions(room.sqft, room.width, room.height);

    return room;
}

Room* firstOfType(std::vector<Room>& rooms, RoomType type) {
    for (Room& room : rooms) {
        if (room.type == type) {
            return &room;
        }
    }

    return nullptr;
}

std::vector<Room*> allOfType(std::vector<Room>& rooms, RoomType type) {
    std::vector<Room*> matches;
    for (Room& room : rooms) {
        if (room.type == type) {
            matches.push_back(&room);
        }
    }

    return matches;
}

int roomWidthSum(const std::vector<Room*>& rooms) {
    int width = 0;
    for (const Room* room : rooms) {
        if (room != nullptr) {
            width += room->width;
        }
    }
    return width;
}

} // namespace

LayoutGenerator::LayoutGenerator() {
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
}

std::vector<Room> LayoutGenerator::buildRoomProgram(const LayoutRequest& request) const {
    const int bedrooms = std::max(0, request.bedrooms);
    const int bathrooms = std::max(0, request.bathrooms);

    float hallwayPercent = 0.0f;
    bool hasHallway = false;

    if (bedrooms == 0) {
        hallwayPercent = 0.0f;
        hasHallway = false;
    } else if (bedrooms == 1) {
        const int roll = std::rand() % 21;
        hallwayPercent = static_cast<float>(roll);
        hasHallway = roll != 0;
    } else {
        hallwayPercent = static_cast<float>((std::rand() % 16) + 5);
        hasHallway = true;
    }

    const float denominator =
        (bedrooms * R_BEDROOM) + (bathrooms * R_BATHROOM) + R_KITCHEN + 1.0f;
    const float x = denominator > 0.0f ? (100.0f - hallwayPercent) / denominator : 0.0f;

    const float livingPercent = x;
    const float totalBedroomPercent = bedrooms * R_BEDROOM * x;
    const float totalBathroomPercent = bathrooms * R_BATHROOM * x;
    const float kitchenPercent = R_KITCHEN * x;

    const std::vector<float> bedroomPercents = distributePercent(bedrooms, totalBedroomPercent);
    const std::vector<float> bathroomPercents = distributePercent(bathrooms, totalBathroomPercent);

    int masterBedroomIndex = 0;
    for (int i = 1; i < static_cast<int>(bedroomPercents.size()); ++i) {
        if (bedroomPercents[i] > bedroomPercents[masterBedroomIndex]) {
            masterBedroomIndex = i;
        }
    }

    int ensuiteBathroomIndex = 0;
    for (int i = 1; i < static_cast<int>(bathroomPercents.size()); ++i) {
        if (bathroomPercents[i] > bathroomPercents[ensuiteBathroomIndex]) {
            ensuiteBathroomIndex = i;
        }
    }

    std::vector<Room> rooms;
    int nextId = 0;

    if (hasHallway) {
        Room hallway = makeRoom(nextId++, RoomType::Hallway, "Hallway", hallwayPercent, request.totalSqft);
        rooms.push_back(hallway);
    }

    rooms.push_back(makeRoom(nextId++, RoomType::LivingRoom, "Living Room", livingPercent, request.totalSqft));
    rooms.push_back(makeRoom(nextId++, RoomType::Kitchen, "Kitchen", kitchenPercent, request.totalSqft));

    for (int i = 0; i < bedrooms; ++i) {
        Room bedroom = makeRoom(
            nextId++,
            RoomType::Bedroom,
            "Bed " + std::to_string(i + 1),
            bedroomPercents[i],
            request.totalSqft
        );
        bedroom.isMaster = (i == masterBedroomIndex);
        rooms.push_back(bedroom);
    }

    for (int i = 0; i < bathrooms; ++i) {
        Room bathroom = makeRoom(
            nextId++,
            RoomType::Bathroom,
            "Bath " + std::to_string(i + 1),
            bathroomPercents[i],
            request.totalSqft
        );
        bathroom.isEnsuite = bathrooms > 1 && (i == ensuiteBathroomIndex);
        rooms.push_back(bathroom);
    }

    return rooms;
}

HouseLayout LayoutGenerator::placeRooms(const LayoutRequest& request, std::vector<Room> rooms) const {
    HouseLayout layout;
    layout.request = request;
    layout.rooms = std::move(rooms);
    layout.hasHallway = firstOfType(layout.rooms, RoomType::Hallway) != nullptr;
    layout.hallwayPercent = 0.0f;

    if (Room* hallway = firstOfType(layout.rooms, RoomType::Hallway)) {
        layout.hallwayPercent = hallway->percent;
    }

    Room* living = firstOfType(layout.rooms, RoomType::LivingRoom);
    Room* kitchen = firstOfType(layout.rooms, RoomType::Kitchen);
    Room* hallway = firstOfType(layout.rooms, RoomType::Hallway);
    std::vector<Room*> bedrooms = allOfType(layout.rooms, RoomType::Bedroom);
    std::vector<Room*> bathrooms = allOfType(layout.rooms, RoomType::Bathroom);

    if (living == nullptr || kitchen == nullptr) {
        return layout;
    }

    preferHorizontal(*living);
    preferHorizontal(*kitchen);

    living->position = {0, 0};
    living->placed = true;

    kitchen->position = {living->right(), 0};
    kitchen->placed = true;

    const int frontRowHeight = std::max(living->height, kitchen->height);

    if (hallway != nullptr) {
        prepareHallway(*hallway);

        Room* masterBedroom = nullptr;
        std::vector<Room*> orderedBedrooms;

        for (Room* bedroom : bedrooms) {
            preferHorizontal(*bedroom);
            if (bedroom->isMaster) {
                masterBedroom = bedroom;
            } else {
                orderedBedrooms.push_back(bedroom);
            }
        }

        if (masterBedroom != nullptr) {
            preferHorizontal(*masterBedroom);
            orderedBedrooms.push_back(masterBedroom);
        }

        Room* ensuiteBathroom = nullptr;
        Room* commonBathroom = nullptr;
        std::vector<Room*> extraBathrooms;

        for (Room* bathroom : bathrooms) {
            preferVertical(*bathroom);
            if (bathroom->isEnsuite && ensuiteBathroom == nullptr) {
                ensuiteBathroom = bathroom;
            } else if (commonBathroom == nullptr) {
                commonBathroom = bathroom;
            } else {
                extraBathrooms.push_back(bathroom);
            }
        }

        std::vector<Room*> mainRow;
        if (commonBathroom != nullptr) {
            mainRow.push_back(commonBathroom);
        }
        for (Room* bedroom : orderedBedrooms) {
            mainRow.push_back(bedroom);
        }
        if (ensuiteBathroom != nullptr) {
            mainRow.push_back(ensuiteBathroom);
        }

        hallway->width = std::max(hallway->width, std::max(living->width + kitchen->width, roomWidthSum(mainRow)));
        hallway->position = {0, frontRowHeight};
        hallway->placed = true;

        const int mainRowY = hallway->bottom();
        int cursorX = 0;
        int mainRowMaxHeight = 0;

        if (commonBathroom != nullptr) {
            commonBathroom->position = {cursorX, mainRowY};
            commonBathroom->placed = true;
            cursorX += commonBathroom->width;
            mainRowMaxHeight = std::max(mainRowMaxHeight, commonBathroom->height);
        }

        for (Room* bedroom : orderedBedrooms) {
            bedroom->position = {cursorX, mainRowY};
            bedroom->placed = true;
            cursorX += bedroom->width;
            mainRowMaxHeight = std::max(mainRowMaxHeight, bedroom->height);
        }

        if (ensuiteBathroom != nullptr) {
            ensuiteBathroom->position = {cursorX, mainRowY};
            ensuiteBathroom->placed = true;
            cursorX += ensuiteBathroom->width;
            mainRowMaxHeight = std::max(mainRowMaxHeight, ensuiteBathroom->height);
        }

        hallway->width = std::max(hallway->width, cursorX);

        const int extraBathroomY = mainRowY + mainRowMaxHeight;
        std::size_t extraAnchorIndex = 0;

        for (Room* bathroom : extraBathrooms) {
            Room* anchor = nullptr;
            if (extraAnchorIndex < orderedBedrooms.size()) {
                anchor = orderedBedrooms[extraAnchorIndex];
            } else if (!orderedBedrooms.empty()) {
                anchor = orderedBedrooms.back();
            } else {
                anchor = living;
            }

            bathroom->position = {anchor->position.x, extraBathroomY};
            bathroom->placed = true;
            ++extraAnchorIndex;
        }
    } else {
        std::vector<Room*> orderedBedrooms;
        for (Room* bedroom : bedrooms) {
            preferHorizontal(*bedroom);
            orderedBedrooms.push_back(bedroom);
        }

        const int secondRowY = frontRowHeight;
        int cursorX = 0;
        int secondRowMaxHeight = 0;

        for (Room* bedroom : orderedBedrooms) {
            bedroom->position = {cursorX, secondRowY};
            bedroom->placed = true;
            cursorX += bedroom->width;
            secondRowMaxHeight = std::max(secondRowMaxHeight, bedroom->height);
        }

        int bathroomX = !orderedBedrooms.empty() ? orderedBedrooms.front()->right() : 0;
        for (Room* bathroom : bathrooms) {
            preferVertical(*bathroom);
            bathroom->position = {bathroomX, secondRowY};
            bathroom->placed = true;
            bathroomX += bathroom->width;
            secondRowMaxHeight = std::max(secondRowMaxHeight, bathroom->height);
        }
    }

    layout.normalizeToOrigin();
    refreshAdjacency(layout);

    return layout;
}

HouseLayout LayoutGenerator::generateLayout(const LayoutRequest& request) const {
    return placeRooms(request, buildRoomProgram(request));
}