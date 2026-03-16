---
name: next layout phases
overview: Define the next implementation steps for evolving the current room-sizing prototype into a class-based house layout generator with placement, validation, and rendering stages.
todos:
  - id: extract-models
    content: Create the first model layer for request, room, position, and grid/house layout data.
    status: completed
  - id: separate-entrypoint
    content: Move CLI input/output into a dedicated main file so LayoutGenerator becomes a reusable system.
    status: completed
  - id: reuse-sizing-phase
    content: Refactor the current percentage and dimension math into a room-program generation step that returns typed room data.
    status: completed
  - id: build-grid-placement
    content: Implement the first room placement algorithm that assigns coordinates and prevents overlapping rectangles.
    status: completed
  - id: add-rule-validator
    content: Create a validator for core adjacency, reachability, hallway, and minimum-size rules after placement.
    status: completed
  - id: render-ascii-layout
    content: Expand output to render an ASCII floor plan from placed rooms plus the existing numeric summary.
    status: completed
isProject: false
---

# Next Steps For House Generator

Your project is at a good checkpoint: the room-size math is working, but the program still stops before the real layout problem starts. The next thing to build is not more percentage logic. It is a real in-memory layout model that can hold room positions, adjacency, and grid occupancy so the rest of your plan can plug into it cleanly.

## What You Have Now

The current code is still a single-stage pipeline:

- `[src/systems/LayoutGenerator.cpp](/Users/avadennis/Documents/after-college-current/projects/house-generator/src/systems/LayoutGenerator.cpp)` collects input, computes percentages, converts them to sqft and dimensions, and stores flat `RoomResult` values.
- `[include/systems/LayoutOutput.h](/Users/avadennis/Documents/after-college-current/projects/house-generator/include/systems/LayoutOutput.h)` defines `RoomResult`, which is really generation data even though it lives in output code.
- `[src/systems/LayoutOutput.cpp](/Users/avadennis/Documents/after-college-current/projects/house-generator/src/systems/LayoutOutput.cpp)` only prints a report table.
- Your planning docs in `[logic-plans/grid-layout-logic.md](/Users/avadennis/Documents/after-college-current/projects/house-generator/logic-plans/grid-layout-logic.md)` and `[logic-plans/house-rules-logic.md](/Users/avadennis/Documents/after-college-current/projects/house-generator/logic-plans/house-rules-logic.md)` assume a later phase where rooms have coordinates and relationships, but that model layer does not exist yet.

Essentially, you have finished the `room program + sizing` phase and should now build the `placement` phase.

## Recommended Architecture

Build the generator as a 4-stage pipeline:

```mermaid
flowchart LR
    userInput[UserInput] --> request[LayoutRequest]
    request --> sizing[LayoutGenerator::buildRoomProgram]
    sizing --> placement[LayoutGenerator::placeRooms]
    placement --> validation[RuleValidator::validate]
    validation --> output[LayoutOutput::render]
```



That means your next class boundaries should be:

- `LayoutRequest`: bedroom count, bathroom count, total sqft.
- `RoomType`: bedroom, bathroom, kitchen, living room, hallway.
- `Room`: room identity plus size data.
- `PlacedRoom`: a room plus `x/y/width/height` and connection metadata.
- `HouseLayout` or `Grid`: owns all placed rooms and the occupied cells.
- `LayoutGenerator`: generates the room program, then places rooms.
- `RuleValidator`: checks the rules after placement.
- `LayoutOutput`: only prints or renders, never decides placement.

## Best Next Implementation Order

1. Extract the data model first.

Create `models` that separate generation data from output formatting. Right now `RoomResult` is doing too much. Start with:

- `[include/models/Position.h](/Users/avadennis/Documents/after-college-current/projects/house-generator/include/models/Position.h)`
- `[include/models/Room.h](/Users/avadennis/Documents/after-college-current/projects/house-generator/include/models/Room.h)`
- `[include/models/Grid.h](/Users/avadennis/Documents/after-college-current/projects/house-generator/include/models/Grid.h)`
- `[include/models/House.h](/Users/avadennis/Documents/after-college-current/projects/house-generator/include/models/House.h)`

Keep these simple. You do not need deep inheritance yet. A `RoomType` enum plus one `Room` class is enough to get placement working. You can add specialized `Bedroom` or `Bathroom` classes later if they truly need unique behavior.

1. Turn `LayoutGenerator` into a real system instead of `main()`.

Move input/output responsibility out of `[src/systems/LayoutGenerator.cpp](/Users/avadennis/Documents/after-college-current/projects/house-generator/src/systems/LayoutGenerator.cpp)`. The generator should expose functions like:

- `buildRoomProgram(const LayoutRequest&)`
- `placeRooms(...)`
- `generateLayout(const LayoutRequest&)`

Then keep `main.cpp` as the CLI entry point only. This matches the system split you already described in `[file-structure.md](/Users/avadennis/Documents/after-college-current/projects/house-generator/file-structure.md)`.

1. Preserve your current math as Phase 1.

Do not rewrite the size math right now. Reuse the hallway roll, percentage solver, room distribution, and dimension calculation from `[logic-plans/math.md](/Users/avadennis/Documents/after-college-current/projects/house-generator/logic-plans/math.md)` as the first step that creates sized `Room` objects.

1. Implement a simple rectangle placement algorithm next.

This is the most important missing feature. Use the output of the math step to assign coordinates. Start with a deterministic heuristic rather than a perfect generator:

- Put `Living Room` and `Kitchen` near the front/top of the layout.
- Put `Hallway` as the central connector when required.
- Put bedrooms in a quieter cluster away from the entrance.
- Attach one bathroom to the master bedroom when possible.
- Prevent overlap by checking each proposed rectangle against already placed rooms.

A good first milestone is: every room has a valid rectangle and no overlap, even if the layout is still rough.

1. Add validation after placement, not during the first pass.

Use `[logic-plans/house-rules-logic.md](/Users/avadennis/Documents/after-college-current/projects/house-generator/logic-plans/house-rules-logic.md)` as a second-stage checker. Start with the rules that are easiest to compute and most important:

- hallway required for `2+` bedrooms
- no overlaps
- all rooms reachable
- kitchen adjacent to living room or hallway
- bedrooms not adjacent to kitchen
- at least one common bathroom touches hallway
- minimum room sizes

This should return either `valid/invalid` plus a list of failed rules. Later you can add repair logic.

1. Upgrade output last.

After placement exists, expand `[src/systems/LayoutOutput.cpp](/Users/avadennis/Documents/after-college-current/projects/house-generator/src/systems/LayoutOutput.cpp)` from a table printer into two outputs:

- summary table of sizes and totals
- ASCII floor-plan rendering based on the grid/placed rooms

That is the point where your current `grid-layout-logic.md` sketch becomes visible in the program.

## Why This Order Fits Your Code

Two small pieces of your current implementation show why this should be the next move:

```32:40:src/systems/LayoutGenerator.cpp
int main() {
    srand((unsigned)time(nullptr));

    int bedrooms, bathrooms, totalSqft;

    std::cout << "\n=== House Layout Math Calculator ===\n\n";
    std::cout << "Enter number of bedrooms  (1-6): "; std::cin >> bedrooms;
    std::cout << "Enter number of bathrooms (1-4): "; std::cin >> bathrooms;
    std::cout << "Enter total square footage:       "; std::cin >> totalSqft;
```

This file is currently acting as app entrypoint, generator, and algorithm host all at once.

```7:13:include/systems/LayoutOutput.h
struct RoomResult {
    std::string name;
    float percent;
    float sqft;
    int width;
    int height;
};
```

This struct is useful, but it belongs in a model/generator layer, and it now needs coordinates and connectivity.

## Practical Milestone To Aim For First

A strong next milestone is:

- input a request
- generate sized rooms
- place each room on a 2D grid with `x/y/width/height`
- print both the room list and a rough ASCII map

If you reach that milestone before adding door logic or full rule coverage, the project will still feel like a real house-layout generator instead of only a calculator.

## Notes On Class Design

Because your project goal is both learning OOP and building a generator, keep the first class pass lightweight:

- Prefer a single `Room` class with a `RoomType` enum first.
- Add `Bedroom`, `Bathroom`, `Kitchen`, and `LivingRoom` subclasses only when they need unique methods or invariants.
- Put algorithms in `systems`, not inside model classes.
- Keep rendering in `LayoutOutput` or a later `Renderer`, not in `Room` or `House`.

That approach will fit your file-structure idea without making the code harder than the layout problem already is.