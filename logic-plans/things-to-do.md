
make getters i house for bed, kit, bath

how to get a list of bed objects? from house?

move position to system - because its functions and does not take up physical space in house

figure out if house and maybe room should be in a different folder

reorganize files in proper function order: i.e constructors, setters, getters, facilitors, descuctors

place the full house on the grid after house is complete, to start it cant be on the grid and checking grid <- hold on i might be wrong because it can check inbetween its positon spots
because 
grid.get_middle_grid_r()+ x is starting point
    // if(x == 0){   <- north 
    //      for (int row = 0; row < house.get_livingroom().get_width(); row++)
    //          if (make_tuple(grid.get_middle_grid_r()-1 + x, grid.get_middle_grid_r()+ row) == '.')
    //              free space
    //          else if (make_tuple(grid.get_middle_grid_r()-1 + x, grid.get_middle_grid_r()+ row) == Room::S)
    //              taken
    // }else if (x == height - 1){ <- south
    //      for width size - inner loop
    //          if (grid.get_middle_grid_r()+ y - 1 == '.')
    //          check height == Room::N
    // }else if (y == width - 1){ <- east
    //      for height size - outer loop
    //          check width = Room::W
    // }else if (y == 0){ <-west
    //      for height size - outer loop
    //          check y - 1 = Room::E
    // }else{ <-inbetween
    //
    // }

