#ifndef DIMENSION_OUTPUT_H
#define DIMENSION_OUTPUT_H

#include <string>
#include <vector>

struct RoomResult {
  std::string name;
  float percent;
  float sqft;
  int width;
  int height;
};

void printRoom(const RoomResult &room);
void printDimensionReport(const std::vector<RoomResult> &rooms,
                           int targetSqft);

#endif

