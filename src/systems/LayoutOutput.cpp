#include "../../include/systems/LayoutOutput.h"

#include <iomanip>
#include <iostream>

void printRoom(const RoomResult& room) {
    std::cout << std::left << std::setw(20) << room.name
              << std::right << std::setw(8) << std::fixed << std::setprecision(2) << room.percent << "%"
              << std::setw(10) << std::fixed << std::setprecision(1) << room.sqft << " sqft"
              << "   " << room.width << "x" << room.height << " ft"
              << "\n";
}

void printLayoutReport(const std::vector<RoomResult>& rooms, bool hasHallway, int targetSqft) {
    std::cout << "\n=== Results ===\n";
    std::cout << std::string(58, '-') << "\n";
    std::cout << std::left << std::setw(20) << "Room"
              << std::right << std::setw(9) << "Percent"
              << std::setw(12) << "Sqft"
              << "   Dimensions\n";
    std::cout << std::string(58, '-') << "\n";

    float totalPercent = 0.0f;
    float totalRoomSqft = 0.0f;

    if (!hasHallway) {
        std::cout << "Hallway: NONE (rolled 0% - entrance via living room or kitchen)\n";
    }

    for (const RoomResult& room : rooms) {
        printRoom(room);
        totalPercent += room.percent;
        totalRoomSqft += room.sqft;
    }

    std::cout << std::string(58, '-') << "\n";
    std::cout << std::left << std::setw(20) << "TOTAL"
              << std::right << std::setw(8) << std::fixed << std::setprecision(2) << totalPercent << "%"
              << std::setw(10) << std::fixed << std::setprecision(1) << totalRoomSqft << " sqft\n";
    std::cout << std::string(58, '-') << "\n";
    std::cout << "\nTarget sqft: " << targetSqft
              << "  |  Actual: " << std::fixed << std::setprecision(1) << totalRoomSqft
              << "  |  Diff: " << std::fixed << std::setprecision(1) << (totalRoomSqft - targetSqft)
              << " sqft\n\n";
}
