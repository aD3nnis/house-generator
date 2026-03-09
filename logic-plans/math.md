1. Roll hallway percentage
   - bedroomCount == 1 → random float between 0% and 23%
     - if roll == 0 → no hallway created
   - bedroomCount > 1  → random float between 2% and 23%

2. Solve for x
   x = (100 - H) / (b·0.7 + a·0.4 + 0.8 + 1)

3. Assign percentages
   Living room:  x
   Each bedroom: 0.7x
   Each bathroom: 0.4x
   Kitchen:      0.8x
   Hallway:      H

4. Convert percentage to sqft
   roomSqft = (roomPercent / 100) * totalSqft

5. Convert sqft to dimensions
   width  = sqrt(roomSqft)
   height = roomSqft / width
   adjust until aspect ratio is under 3:1