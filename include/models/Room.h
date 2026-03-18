#pragma once

#include <functional>
#include <map>
#include <random>
#include <string>
#include <tuple>
#include <vector>

class DimensionGenerator;
class Room;

// rooms can be categorized by any type
enum class RoomType { Bedroom, Kitchen, Livingroom, Bathroom };

struct AnchorChoiceContext {
  const std::vector<Room *> &placed;
  std::vector<Room *> kitchens;
  std::vector<Room *> Livingrooms;
  std::vector<Room *> bedrooms;
  std::vector<Room *> bathrooms;
  std::function<bool(Room *)> has_free_side;
};

class Room {
private:
  int width{};  // inner loop but also y
  int height{}; // outer loop but also x
  float room_sqft{};
  std::string name = "Room";
  char name_symbol = 'R';
  std::map<std::tuple<int, int>, char> walls;
  int anchorXOnGrid;
  int anchorYOnGrid;

public:
  static constexpr char N = '_';
  static constexpr char S = '-';
  static constexpr char E = '!';
  static constexpr char W = '|';
  static std::mt19937 &rng(); // mt19937 is a random number generator

  Room() : width(0), height(0), room_sqft(0.0f) {}
  Room(const std::string &n, char n_s) : name(n), name_symbol(n_s) {}

  void set_anchor(int x, int y) {
    anchorXOnGrid = x;
    anchorYOnGrid = y;
  }
  int get_anchor_x() const { return anchorXOnGrid; }
  int get_anchor_y() const { return anchorYOnGrid; }

  int get_width() { return width; }
  int get_height() { return height; }

  void set_room_sqft(float percent, float totalSqft);
  float get_room_sqft();

  void update_dimensions(DimensionGenerator &dimension_gen);

  void make_walls_of_room();
  void place_name_in_room();
  std::map<std::tuple<int, int>, char> get_room() { return walls; }

  virtual RoomType get_type() const = 0;
  virtual Room *pick_anchor(const AnchorChoiceContext &ctx) const = 0;
  virtual float get_default_size_ratio() const = 0;
  virtual ~Room() = default;
};