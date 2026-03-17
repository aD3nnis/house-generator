#include "../../include/models/Room.h"
#include "../../include/systems/LayoutGenerator.h"

#include <iostream>
#include <tuple>
#include <utility>

    void Room::set_room_sqft(float percent, float totalSqft) {
  room_sqft = (percent / 100.0f) * totalSqft;
}

float Room::get_room_sqft() { return room_sqft; }

void Room::update_dimensions(LayoutGenerator &layout_gen) {
  layout_gen.calcDimensions(room_sqft, width, height);
}

void Room::display_w_h(Room &r) const {
  std::cout << "w: " << r.width << " h: " << r.height;
}

void Room::make_walls_of_room() {
  for (int x = 0; x < height; x++) {
    for (int y = 0; y < width; y++) {
      std::tuple<int, int> key{x, y};
      if (x == 0) {
        walls[key] = Room::N;
      } else if (x == height - 1) {
        walls[key] = Room::S;
      } else if (y == width - 1) {
        walls[key] = Room::E;
      } else if (y == 0) {
        walls[key] = Room::W;
      } else {
        walls[key] = ' ';
      }
    }
  }
}

void Room::place_name_in_room() {
  auto key = std::make_tuple(height / 2, width / 2);
  walls[key] = name_symbol;
}

void Room::display_room_grid() {
  for (int x = 0; x < height; x++) {
    for (int y = 0; y < width; y++) {
      auto key = std::make_tuple(x, y);
      std::cout << walls[key] << ' ';
    }
    std::cout << std::endl;
  }
}

std::mt19937 &Room::rng() {
  static std::mt19937 engine(
      42); // 42 is a seed for the random number generator
  return engine;
}
