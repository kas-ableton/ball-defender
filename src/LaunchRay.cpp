#include "LaunchRay.hpp"
#include <cmath>

namespace bd {
LaunchRay::LaunchRay(const Point& origin) : mOrigin(origin) {}

void LaunchRay::onDragStart(const Point& start) { mDragStart = start; }

void LaunchRay::onDragUpdate(const Point& end) { mDragEnd = end; }

Point LaunchRay::origin() const { return mOrigin; }

Point LaunchRay::terminus() const {
  auto diff = mDragStart - mDragEnd;
  return mOrigin + diff;
}

float LaunchRay::length() const {
  const auto t = terminus();
  const float x1 = t.x();
  const float y1 = t.y();
  const float x2 = mOrigin.x();
  const float y2 = mOrigin.y();
  return std::sqrt(std::powf(x1 - x2, 2) + std::powf(y1 - y2, 2));
}

float LaunchRay::angle() const {
  const auto t = terminus();
  const float x1 = t.x();
  const float y1 = t.y();
  const float x2 = mOrigin.x();
  const float y2 = mOrigin.y();

  return std::atan2(y2 - y1, x2 - x1) * 180.0 / 3.141592653589793238463;
}

} // namespace bd
