#include "Point.hpp"

namespace bd {
Point::Point()
    : mX(std::numeric_limits<int>::max()), mY(std::numeric_limits<int>::max()) {
}

Point::Point(int _x, int _y) : mX(_x), mY(_y) {}

void Point::setX(int _x) { mX = _x; }
void Point::setY(int _y) { mY = _y; }
void Point::set(int _x, int _y) {
  mX = _x;
  mY = _y;
}

int Point::x() const { return mX; }
int Point::y() const { return mY; }

} // namespace bd
