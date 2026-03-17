#include "../../include/models/Kitchen.h"

float Kitchen::get_default_size_ratio()
{
    return R_KITCHEN;
}
Room* Kitchen::pick_anchor(const AnchorChoiceContext& ctx) const
{
    for (Room* lr : ctx.Livingrooms) {
        if (ctx.has_free_side(lr)) return lr;
    }
    for (Room* r : ctx.placed) {
        if (ctx.has_free_side(r)) return r;
    }
    if (!ctx.placed.empty())
        return ctx.placed[rand() % ctx.placed.size()];
    return nullptr;
}