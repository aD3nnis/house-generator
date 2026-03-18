#include "../../include/systems/DimensionOutput.h"

#include <iomanip>
#include <iostream>

// prints the room results in a table format
// I let cursor write output of the dimensions table for me

void printRoom(const RoomResult &room) {
  std::cout << std::left << std::setw(20) << room.name << std::right
            << std::setw(8) << std::fixed << std::setprecision(2)
            << room.percent << "%" << std::setw(10) << std::fixed
            << std::setprecision(1) << room.sqft << " sqft"
            << "   " << room.width << "x" << room.height << " ft"
            << "\n";
}

void printDimensionReport(const std::vector<RoomResult> &rooms,
                           int targetSqft) {
  std::cout << "\n=== Results ===\n";
  std::cout << std::string(58, '-') << "\n";
  std::cout << std::left << std::setw(20) << "Room" << std::right
            << std::setw(9) << "Percent" << std::setw(12) << "Sqft"
            << "   Dimensions\n";
  std::cout << std::string(58, '-') << "\n";

  float totalPercent = 0.0f;
  float totalRoomSqft = 0.0f;

  for (const RoomResult &room : rooms) {
    printRoom(room);
    totalPercent += room.percent;
    totalRoomSqft += room.sqft;
  }

  std::cout << std::string(58, '-') << "\n";
  std::cout << std::left << std::setw(20) << "TOTAL" << std::right
            << std::setw(8) << std::fixed << std::setprecision(2)
            << totalPercent << "%" << std::setw(10) << std::fixed
            << std::setprecision(1) << totalRoomSqft << " sqft\n";
  std::cout << std::string(58, '-') << "\n";
  std::cout << "\nTarget sqft: " << targetSqft << "  |  Actual: " << std::fixed
            << std::setprecision(1) << totalRoomSqft
            << "  |  Diff: " << std::fixed << std::setprecision(1)
            << (totalRoomSqft - targetSqft) << " sqft\n\n";
}

