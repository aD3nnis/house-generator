# House Layout Generator (Interview Overview)

## What it is
`house-generator` is a C++ console program that procedurally generates a simple residential floor plan. Given a target number of bedrooms, bathrooms, and total square footage, it:
1. Computes per-room size targets (via percentages).
2. Converts those targets into integer grid dimensions.
3. Places rooms on an ASCII grid while respecting adjacency rules (no "side connections" into already-occupied space).
4. Prints both a dimensions table and a visual floor plan.

## Inputs and constraints
The program prompts for:
- `bedrooms`: constrained to `1-4`
- `bathrooms`: constrained to `1-3`
- `totalSqft`: constrained to `500-1000`

Then it can be rerun interactively (`y/n`).

## High-level generation flow
At a high level, `main.cpp` orchestrates the pipeline:
- Build a `House` with the requested room counts.
- Compute "base" space ratios (living room, then derived totals for bedrooms/bathrooms, plus kitchen).
- Randomly distribute each room category's total percentage into individual rooms (`DimensionGenerator::distributePercent`).
- Create each room's internal representation (`House::create_rooms`):
  - set room sqft
  - compute width/height (`DimensionGenerator::calcDimensions`)
  - generate wall cells + place a room label in the center (`Room::make_walls_of_room`, `Room::place_name_in_room`)
- Place rooms on the `Grid` (`Position`):
  - place the living room anchored near the grid center
  - compute which outer sides are "free" vs "taken" using neighbor checks around the living room
  - attach remaining rooms (kitchen, bedrooms, bathrooms) one-by-one by picking an anchor room + choosing a random free side
- Output:
  - print a room-by-room dimension report (`printDimensionReport`)
  - render the final ASCII floor plan (`Grid::display_grid`)

## Core abstractions (what to mention in an interview)
### `Room` (polymorphic base)
`Room` is an abstract base that stores:
- grid dimensions (`width`, `height`)
- an anchor position on the grid (`set_anchor`, `get_anchor_x/y`)
- a wall/contents map (`walls`) represented as characters

It's also where the program's extensibility lives:
- `get_default_size_ratio()` controls baseline size scaling per room type
- `pick_anchor(ctx)` decides which already-placed room(s) it can attach to

### `House` (room collection + percent logic)
`House` owns the concrete room objects:
- `Livingroom` (single)
- `Kitchen` (single)
- `vector<Bedroom>`
- `vector<Bathroom>`

It centralizes the "how much space does each category get?" logic:
- `set_room_percentages()` sets living, bedroom total, bathroom total, and kitchen total percentages
- `create_rooms()` applies those percentages to produce final dimensions + ASCII walls for each room

### `DimensionGenerator` (sqft -> dimensions + weighted distribution)
`DimensionGenerator` handles two key transforms:
- `distributePercent(roomCount, totalPercent)`:
  - picks random weights in a range (variation factor)
  - normalizes them to distribute the category's total percentage across individual rooms
- `calcDimensions(sqft, width, height)`:
  - converts sqft into integer grid dimensions (width from `sqrt(sqft)`, height from `sqft/width`)

### `Grid` + `Position` (spatial layout on a discrete map)
`Grid` stores a 2D-ish representation as a `map<(x,y), char>` and renders it as ASCII.

`Position` is responsible for placement decisions:
- `check_if_side_taken()` inspects cells adjacent to a room's four sides to decide which sides can be used for connections
- `pick_random_free_side()` chooses one free side and sets the new room's anchor so it connects cleanly
- `place_rooms_random()` uses an `AnchorChoiceContext` to let different room types choose anchors via polymorphism, while still using the shared placement mechanics

## Key interview talking points
- **OOP + polymorphism for room-specific placement rules:** room types implement `pick_anchor()` so the layout algorithm avoids a giant `if/else` block.
- **Separation of concerns:** sizing (`House` + `DimensionGenerator`) is decoupled from placement (`Position`) and rendering (`Grid`).
- **Discrete constraint solving:** adjacency is enforced by checking neighboring grid cells and only connecting via "free sides".
- **Procedural variety:** per-room percentages are randomized, and the attachment side selection is randomized, so repeated runs produce different layouts.
- **Extensibility:** adding a new room type would typically mean creating a new `Room` subclass and teaching `pick_anchor()` and the size ratio.

## Notes on randomness (optional detail)
The code uses both `rand()/srand(time(...))` for placement/weighting and a static `mt19937` RNG for some shuffles, so results vary run-to-run while still having some deterministic elements inside specific selection logic.

