#pragma once

#include <limits>

namespace bd {
class Point;

class Vector {
public:
    enum class Axis {
        X,
        Y,
    };
  Vector() = default;
  Vector(Point&& startPos, Point&& endPos);

  void reflect(const Axis axis);
  void reset();

  float x = std::numeric_limits<float>::min();
  float y = std::numeric_limits<float>::min();
};
} // namespace bd
