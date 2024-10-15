#include "Point.hpp"

namespace bd {
Point operator-(const Point& point, int value) {
  return {point.x() - value, point.y() - value};
}

Point::Point()
    : mX(std::numeric_limits<int>::max()), mY(std::numeric_limits<int>::max()) {
}

Point::Point(int _x, int _y) : mX(_x), mY(_y) {}

Point::Point(const Point& other) : mX(other.x()), mY(other.y()) {}

void Point::setX(int _x) { mX = _x; }
void Point::setY(int _y) { mY = _y; }
void Point::set(int _x, int _y) {
  mX = _x;
  mY = _y;
}

int Point::x() const { return mX; }
int Point::y() const { return mY; }

} // namespace bd
