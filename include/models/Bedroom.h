#pragma once

#include "Room.h"

class Bedroom : public Room {
private:
  static constexpr float R_BEDROOM = 0.7f;

public:
  float get_default_size_ratio() const override;
  Bedroom() : Room("Bedroom", 'B') {}
  RoomType get_type() const override { return RoomType::Bedroom; }
  Room *pick_anchor(const AnchorChoiceContext &ctx) const override;
};
