#pragma once
#ifndef DIMENSION_GENERATOR_H
#define DIMENSION_GENERATOR_H

#include "DimensionOutput.h"
#include <vector>

class DimensionGenerator {
private:
  const float MIN_ROOM_VARIATION = 0.85f; // minimum room variation
  const float MAX_ROOM_VARIATION = 1.25f; // maximum room variation

public:
  float get_min_room_variation();
  float get_max_room_variation();

  // Convert sqft to dimensions with max 3:1 aspect ratio
  void calcDimensions(float &sqft, int &width, int &height);

  std::vector<float> distributePercent(int roomCount, float totalPercent,
                                        DimensionGenerator &dimension_gen);
  float randomWeight(DimensionGenerator &dimension_gen);
};

#endif

