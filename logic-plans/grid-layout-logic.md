

How the layout grid should work.

The house contains a 2D grid layout that rooms are placed into.

Example Layout simulation
input: 
bedrooms:   3   → valid (1-4)
bathrooms:  2   → valid (1-4)
sqft:       1800 → valid (500-5000)

layout:

useable area example: 
Total usable area: 1800 sqft

Living Room:   ~18% → 324 sqft  → 18x18
Kitchen:       ~12% → 216 sqft  → 12x18
Bedroom 1:     ~10% → 216 sqft  → 12x18  (master)
Bedroom 2:     ~18% → 180 sqft  → 12x15
Bedroom 3:     ~18% → 180 sqft  → 12x15
Bathroom 1:    ~5%  →  90 sqft  →  9x10
Bathroom 2:    ~5%  →  90 sqft  →  9x10
Hallway:       ~8%  → 144 sqft  →  6x24

Total accounted for: ~1800 sqft ✓

Output:

(0,0)─────────────────────────────────(50,0)
  │  Living Room  │    Kitchen         │
  │  18x18        │    12x18           │
  ├───────────────┴────────────────────┤
  │           Hallway (6x24)           │
  ├──────────┬──────────┬──────────────┤
  │ Bedroom1 │ Bedroom2 │ Bedroom3     │
  │ 12x18    │ 12x15    │ 12x15        │
  ├──────────┴──────────┤              │
  │ Bathroom1 │Bath2    │              │
  │ 9x10      │9x10     │              │
(0,36)────────────────────────────────(50,36)