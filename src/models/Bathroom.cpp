#include "../../include/models/Bathroom.h"

float Bathroom::get_default_size_ratio()
{
    return R_BATHROOM;
}
Room* Bathroom::pick_anchor(const AnchorChoiceContext& ctx) const
{
    vector<Room*> allowed;
    for (Room* r : ctx.Livingrooms) allowed.push_back(r);
    for (Room* r : ctx.kitchens) allowed.push_back(r);
    for (Room* r : ctx.bedrooms) allowed.push_back(r);

    shuffle(allowed.begin(), allowed.end(), rng());
    
    for (Room* r : allowed) {
        if (ctx.has_free_side(r)) return r;
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