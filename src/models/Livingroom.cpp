#include "../../include/models/Livingroom.h"

float Livingroom::get_default_size_ratio() const { return livingroom_size; }

void Livingroom::set_livingroom_size(float bedrooms, float bed_size,
                                     float bathrooms, float bath_size,
                                     float kit_size) {
  float denominator =
      (bedrooms * bed_size) + (bathrooms * bath_size) + kit_size + 1.0f;
  float x = (100.0f) / denominator;
  livingroom_size = x;
}

Room* Livingroom::pick_anchor(const AnchorChoiceContext& ctx) const {
  if (ctx.placed.empty())
    return nullptr;
  return ctx.placed[std::rand() % ctx.placed.size()];
}