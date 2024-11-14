#pragma once

#include <limits>

namespace bd {
class Point;

class Vector {
public:
  static Vector reflect(const Vector& vector, const Vector& surfaceNormal);

    enum class Axis {
        X,
        Y,
    };
  Vector() = default;
  Vector(const Vector& v);
  Vector(Point&& startPos, Point&& endPos);
  constexpr Vector(float X, float Y) : x(X), y(Y) {}

  Vector reflect(const Vector& other);
  void reflect(const Axis axis);
  void reset();

  float x = std::numeric_limits<float>::min();
  float y = std::numeric_limits<float>::min();
};
} // namespace bd
