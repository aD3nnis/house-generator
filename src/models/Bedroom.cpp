#include "../../include/models/Bedroom.h"

#include <algorithm>
#include <vector>

// scope resolution operator (::) so same function but different namespace
float Bedroom::get_default_size_ratio() const { return R_BEDROOM; }

Room* Bedroom::pick_anchor(const AnchorChoiceContext& ctx) const {
  std::vector<Room*> allowed;
  for (Room* r : ctx.Livingrooms)
    allowed.push_back(r);
  for (Room* r : ctx.kitchens)
    allowed.push_back(r);

  // Prefer Kitchen or Livingroom, random order
  std::shuffle(allowed.begin(), allowed.end(), rng());

  for (Room* r : allowed) {
    if (ctx.has_free_side(r))
      return r;
  }

  // Fallback: any placed room with free side
  for (Room* r : ctx.placed) {
    if (ctx.has_free_side(r))
      return r;
  }

  // Last resort: random placed room
  if (!ctx.placed.empty())
    return ctx.placed[std::rand() % ctx.placed.size()];
  return nullptr;
}