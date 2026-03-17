#ifndef LAYOUT_OUTPUT_H
#define LAYOUT_OUTPUT_H

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
void printLayoutReport(const std::vector<RoomResult> &rooms, int targetSqft);

#endif
