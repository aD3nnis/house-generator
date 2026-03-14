Class House
House will have room objects
in a house all rooms will be touching either the kitchen or livingroom

Parent Class: Room
    Room attributes: 
        - 4 walls/sides (what does this mean? thinking coordinates)
        - 1 door 
        - length
        - width
        
    methods: 
    size -> this should by polymorphism because each size will be calculated differently 
        (same name different work)
    position -> polymorphism?
        Bed:
            bed 1 side = 1 side kitchen || bed 1 side = 1 side livingroom
        Bath: 
            Bath 1 side = 1 side kitchen || Bath 1 side = 1 side livingroom || Bath 1 side = 1 side Bed
        Kitchen:
            kitchen 1 side = 1 side Livingroom
        Livingroom:
            livingroom 1 side = 1 side kitchen

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
                  size -> (calculation?)

Helper functions: 


Class Position // maybe for function below
attribute: 
get size of house? // so i can have grid?

check if side taken(){ // could be a member function of room? maybe position?
    // check if side of Room is taken
    // if yes choose a different viable side
    // example: 

    for(each living room side){
        if (Living room side i open){
            bed side 1 = living room side i
            // not sure yet which one
            return living room side?
            return; // break?
        }
    }
}
