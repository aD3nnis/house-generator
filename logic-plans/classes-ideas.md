

Class House
House will have room objects

Parent Class: Room
    Room attributes: 
        - 4 walls
        - 1 door
        - length
        - width
        
    methods: 
    size -> this should by polymorphism because each size will be calculated differently 
        (same name different work)

    Child Classes: Bedroom, Bathroom, Kitchen, Livingroom
        Bedroom: 
            attributes/properties:
                - at least 1 window?
            method: 
                size -> (const float R_BEDROOM  = 0.7f;)
        Bathroom:
            attributes/properties:
                - does not need a window
            method: 
                 size -> (const float R_BATHROOM = 0.4f;)
        Kitchen:
            attributes/properties:
                - does need a window
            method:
                  size -> (const float R_KITCHEN  = 0.8f;)
        Livingroom:
            attributes/properties:
                - does not need a window
            method:
                  size -> (?)


