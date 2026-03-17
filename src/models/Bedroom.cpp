#include "../../include/models/Bedroom.h"
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
    // Prefer Kitchen or Livingroom, random order
    if (rand() % 2 == 0) {
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
    // Last resort: random placed room
    if (!ctx.placed.empty())
        return ctx.placed[rand() % ctx.placed.size()];
    return nullptr;
}