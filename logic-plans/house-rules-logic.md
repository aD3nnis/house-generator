###Rules:
ideas for rules

**Connectivity Rules**
if no hallway
1. Bedrooms must connect to a hallway (never directly to a kitchen or living room).
2. Bathrooms must connect to either a hallway or a bedroom — never directly to a kitchen or living room.
3. At least one bathroom must share a wall with a hallway (the "common" bathroom).
4. Bathrooms cannot share walls with other bathrooms.
5. The kitchen must be adjacent to either the living room or a hallway.
6. The living room must be accessible from the hallway.
7. Every room must be reachable from every other room (no isolated rooms — full graph connectivity).

the front entrance must connect to a hallway, kitchen, or living room

**Hallway Rules**

8. At least one hallway must exist if there are 2+ bedrooms.
9. Hallways must connect to at least 2 rooms.
10. Hallways cannot be dead ends (they must pass through or branch).
11. Hallway length scales with bedroom count — more bedrooms require longer or branching hallways.

**Bathroom Rules**

12. There must be at least 1 bathroom per 2 bedrooms, rounded up.
13. At least one bathroom must be a "master" bath directly connected to the largest bedroom if bedroom count ≥ 2.
14. No more than 1 bathroom may share a wall with any single bedroom.

**Bedroom Rules**

15. Bedrooms should not share walls with the kitchen.
16. The master bedroom (largest) should be positioned away from the entrance/front of the house.
    - if 2+ bathrooms one bathroom must share a wall with the master bedroom
17. Each bedroom must have at least 1 door to a hallway or bathroom.

**Kitchen & Living Room Rules**

18. The kitchen must have exactly 1 entry point (door) to prevent it being a throughway.
19. The living room should be adjacent to the front entrance of the house.
20. The kitchen and living room together should occupy at least 20% of total square footage.

**Size & Area Rules**

21. No room may be smaller than 60 sqft (a 6x10 minimum).
22. Hallways must be at least 4 feet wide.
23. Bathrooms must be at least 40 sqft.
24. The sum of all room areas must not exceed total square footage by more than 5% (accounting for walls).
25. Walls have thickness (e.g. 6 inches) and must be factored into total area calculation.
26. No room's largest dimension may exceed 3x its smallest (prevents impractical long/thin rooms).

**Door Rules**

27. Every room must have at least 1 door.
28. Doors must be placed on shared walls between adjacent rooms or hallways — not on exterior walls unless it's the front/back entrance.
29. The house must have exactly 1 front door on an exterior wall, and may have 1 back door.
30. No two doors may be placed on the same wall segment if the wall is shorter than 8 feet.

**Layout & Grid Rules**

31. Rooms must not overlap on the grid.
32. All rooms must tile together with no gaps (fully enclosed floor plan).
33. The overall house shape must be roughly rectangular — L-shapes allowed, but no disconnected wings.
34. Exterior walls must form a closed, continuous perimeter.

**Edge Case / Validation Rules**

35. If square footage is too small for the requested rooms, the program should warn the user and either reduce room sizes to minimums or reduce room count.
36. If bedroom count is 0, no hallway is required and the layout collapses to a studio-style arrangement.
37. If bathroom count exceeds bedroom count, extra bathrooms must still connect to hallways (not float freely).
38. A single-bedroom house with 1 bathroom does not require a hallway — the bathroom may connect directly to the bedroom.