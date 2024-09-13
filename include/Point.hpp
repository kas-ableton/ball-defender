#pragma once

#include <limits>

namespace bd {
struct Point {
  Point();
  Point(int _x, int _y);

  explicit operator bool() const {
    return x != std::numeric_limits<int>::max() &&
           y != std::numeric_limits<int>::max();
  }

  bool operator==(const Point& rhs) const {
    return x == rhs.x && y == rhs.y;
  }

  int x;
  int y;
};
} // namespace bd
