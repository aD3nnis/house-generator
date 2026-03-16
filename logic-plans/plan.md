## The Goal
### C++ Home Layout Modeling System
The goal of the project is to **build a simplified architectural layout generator that models houses using object-oriented C++.**.

Techincally build a program that represents a house as objects (rooms, walls, floors) and can automatically generate and analyze a floor plan.

So the program would:

1. **Take inputs** about a house

   * number of bedrooms
   * number of bathrooms
   * maybe total square footage

2. **Create objects that represent the house**

   * `House`
   * `Room`
   * `Bedroom`
   * `Kitchen`
   * `Bathroom`
   * `Wall`
   * `Door`

3. **Generate a layout**

   * arrange rooms logically
   * store their dimensions
   * track their positions

4. **Output useful information**

   * floor plan (ASCII grid)
   * total square footage
   * list of rooms

---


# What the Program Might Look Like When Someone Runs It

Example run:

```
Enter number of bedrooms: 3
Enter number of bathrooms: 2
Enter square footage: 1800
```

Program generates:

```
Generated Floor Plan

+-------------+-------------+
| Bedroom     | Bedroom     |
| 12x12       | 12x12       |
+-------------+-------------+
| Bathroom    | Hallway     |
+-------------+-------------+
| Kitchen     | Living Room |
+-------------+-------------+

Total Area: 1784 sqft
Rooms: 6
```

---

# The Engineering Goal

The project should demonstrates:

### Object-Oriented Design

Model real-world things as objects.

```
House
 ├── Rooms
 ├── Walls
 ├── Doors
```

---

### System Design

Organize a program into logical components.

```
Input System
Layout Generator
House Model
Renderer
```

---

### Algorithms

Your code decides **where rooms go**.

Example rule:

```
bedrooms near bathrooms
kitchen near living room
hallways connect spaces
```

---
