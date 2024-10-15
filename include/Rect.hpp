#pragma once

#include "Point.hpp"

#include <iostream>

namespace bd {
struct Rect {
  Rect(const Point& topLeft, int height, int width);
  Rect(const Point& topLeft, int side);

  int top() const;
  int bottom() const;
  int left() const;
  int right() const;

  int height() const;
  int width() const;

  bool intersects(const Rect& other);
  bool contains(const Point& point);
  std::optional<Rect> overlap(const Rect& other);

  void shiftX(int value);
  void shiftY(int value);

  Point topLeft;
  Point bottomRight;
};

std::ostream& operator<<(std::ostream& os, const Rect& rect);
} // namespace bd
