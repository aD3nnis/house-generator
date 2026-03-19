#include "../../include/models/Bedroom.h"
#include <random>

// scope resolution operator (::) so same function but different namespace
float Bedroom::get_default_size_ratio()
{
    return R_BEDROOM;
}

Room* Bedroom::pick_anchor(const AnchorChoiceContext& ctx) const {
    auto try_list = [&](const vector<Room*>& rooms) -> Room* {
        for (Room* r : rooms) {
            if (ctx.has_free_side(r)) return r;
        }
        return nullptr;
    };
    // Prefer Kitchen or Livingroom, random order using shared RNG
    std::uniform_int_distribution<int> coin(0, 1);
    if (coin(Room::rng()) == 0) {
        Room* a = try_list(ctx.livingrooms);
        if (a) return a;
        a = try_list(ctx.kitchens);
        if (a) return a;
    } else {
        Room* a = try_list(ctx.kitchens);
        if (a) return a;
        a = try_list(ctx.livingrooms);
        if (a) return a;
    }
    // Fallback: any placed room with free side
    for (Room* r : ctx.placed) {
        if (ctx.has_free_side(r)) return r;
    }
    // Last resort: random placed room using shared RNG
    if (!ctx.placed.empty()) {
        std::uniform_int_distribution<size_t> dist(0, ctx.placed.size() - 1);
        return ctx.placed[dist(Room::rng())];
    }
    return nullptr;
}