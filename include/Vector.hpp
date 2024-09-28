#pragma once

#include <limits>

namespace bd {
class Point;

class Vector {
public:
  Vector() = default;
  Vector(Point&& startPos, Point&& endPos);

  float xDelta = std::numeric_limits<float>::min();
  float yDelta = std::numeric_limits<float>::min();
};
} // namespace bd
