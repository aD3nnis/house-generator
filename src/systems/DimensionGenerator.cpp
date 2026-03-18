#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "../../include/systems/DimensionGenerator.h"

// the code behind these functions was handled by cursor. 
// I determined the logic of wanting a random weight between a variation for multiples of the same room
// i.e bedrooms and bathrooms

float DimensionGenerator::get_min_room_variation() { return MIN_ROOM_VARIATION; }

// returns the maximum room variation
float DimensionGenerator::get_max_room_variation() { return MAX_ROOM_VARIATION; }

// converts sqft to dimensions, how many feet wide and how many feet tall the room is
void DimensionGenerator::calcDimensions(float &sqft, int &width, int &height) {
  width = (int)sqrt(sqft); // width is the square root of the square footage
  if (width < 1)
    width = 1;
  height = (int)(sqft / width); // height is the square footage divided by the width
  if (height < 1)
    height = 1;
}

// distributes the total percentage of the rooms for bedrooms, and bathrooms.
vector<float> DimensionGenerator::distributePercent(int room_count,
                                                          float totalPercent,
                                                          DimensionGenerator &dimension_gen) {
  vector<float> percents;
  if (room_count <= 0)
    return percents;

  vector<float> weights;
  float totalWeight = 0.0f;

  for (int i = 0; i < room_count; i++) {
    float weight = randomWeight(dimension_gen); // random weight between MIN_ROOM_VARIATION and MAX_ROOM_VARIATION
    weights.push_back(weight);
    totalWeight += weight; // calculate the total weight of the rooms
  }

  for (float weight : weights) {
    percents.push_back((weight / totalWeight) *
                       totalPercent); // calculate the percentage of each room
                                      // as a share of the total percentage
  }

  return percents;
}

// returns a random weight between MIN_ROOM_VARIATION and MAX_ROOM_VARIATION
float DimensionGenerator::randomWeight(DimensionGenerator &dimension_gen) {
  float t = (float)rand() / (float)RAND_MAX; // random number between 0 and 1

  // random weight between MIN_ROOM_VARIATION and MAX_ROOM_VARIATION
  return dimension_gen.get_min_room_variation() + t * (dimension_gen.get_max_room_variation() - dimension_gen.get_min_room_variation());
}

