#pragma once

#include <limits>

namespace bd {

struct Point;

Point operator-(const Point& point, int value);
Point operator+(const Point& point, int value);
Point operator-(const Point& point, const Point& point2);
Point operator+(const Point& point, const Point& point2);

struct Point {
  Point();
  Point(int _x, int _y);
  Point(const Point&);

  explicit operator bool() const {
    return mX != std::numeric_limits<int>::max() &&
           mY != std::numeric_limits<int>::max();
  }

  bool operator==(const Point& rhs) const {
    return mX == rhs.x() && mY == rhs.y();
  }

  void setX(int _x);
  void setY(int _y);
  void set(int _x, int _y);

  int x() const;
  int y() const;

private:
  int mX;
  int mY;
};
} // namespace bd
