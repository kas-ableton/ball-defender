#include "Point.hpp"
#include "Vector.hpp"

#include <cmath>

namespace bd {

float dot(const Vector& v, const Vector& w) { return v.x * w.x + v.y * w.y; }

Vector operator+(const Vector& v, const Vector& w) {
  return {v.x + w.x, v.y + w.y};
}

Vector operator-(const Vector& v, const Vector& w) {
  return {v.x - w.x, v.y - w.y};
}

Vector operator*(float value, const Vector& v) {
  return {value * v.x, value * v.y};
}

Vector Vector::reflect(const Vector& vector, const Vector& surfaceNormal) {
  return vector - 2 * dot(vector, surfaceNormal) * surfaceNormal;
}

Vector::Vector(const Vector& v) : x(v.x), y(v.y) {
}

Vector::Vector(Point&& startPos, Point&& endPos) {
  int xMove = startPos.x() - endPos.x();
  int yMove = startPos.y() - endPos.y();

  // length of the vector
  auto r = std::sqrt(xMove * xMove + yMove * yMove);

  // get normalized values of x and y
  y = yMove / r;
  x = xMove / r;
}


void Vector::reflect(const Axis axis) {
  if (axis == Axis::Y) {
    x *= -1;
  } else {
    y *= -1;
  }
}

void Vector::reset() {
  x = std::numeric_limits<float>::min();
  y = std::numeric_limits<float>::min();
}
} // namespace bd
