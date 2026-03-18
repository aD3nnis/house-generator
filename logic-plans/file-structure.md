### brainstorm of layout
just an idea to start 
house-layout/
│
├── CMakeLists.txt
├── README.md
│
├── include/              
│   ├── models/
│   │   ├── Position.h
│   │   ├── Room.h
│   │   ├── Bedroom.h
│   │   ├── Bathroom.h
│   │   ├── Kitchen.h
│   │   ├── LivingRoom.h
│   │   ├── Hallway.h
│   │   ├── House.h
│   │   └── Grid.h
│   │
│   ├── systems/
│   │   ├── DimensionGenerator.h
│   │   ├── RuleValidator.h
│   │   └── Renderer.h
│   │
│   └── utils/
│       └── MathUtils.h         
│
├── src/                         
│   ├── main.cpp
│   │
│   ├── models/
│   │   ├── Room.cpp
│   │   ├── Bedroom.cpp
│   │   ├── Bathroom.cpp
│   │   ├── Kitchen.cpp
│   │   ├── LivingRoom.cpp
│   │   ├── Hallway.cpp
│   │   ├── House.cpp
│   │   └── Grid.cpp
│   │
│   ├── systems/
│   │   ├── DimensionGenerator.cpp
│   │   ├── RuleValidator.cpp
│   │   └── Renderer.cpp
│   │
│   └── utils/
│       └── MathUtils.cpp
│
└── tests/                          # Unit tests (optional)
    ├── test_grid.cpp
    ├── test_rules.cpp
    └── test_layout.cpp