#ifndef LIVINGROOM_H
#define LIVINGROOM_H
#include <iostream>
using namespace std;

#include "Room.h"

class Livingroom : public Room {
private:
  float livingroom_size;

public:
  float get_default_size_ratio() const override;
  Livingroom() : Room("Livingroom", 'L') {}
  RoomType get_type() const override { return RoomType::Livingroom; }
  Room* pick_anchor(const AnchorChoiceContext& ctx) const override;
  // my formula for room size: x = (100) / (b*r1 + a*r2 + r3 + 1)
  void set_livingroom_size(float bedrooms, float bed_size, float bathrooms,
                           float bath_size, float kit_size);
};
#endif