#pragma once

#include "Point.hpp"

namespace bd
{
class Vector;

class LaunchRay {
public:
  LaunchRay(const Point& origin);
  void onDragStart(const Point& start);
  void onDragUpdate(const Point& end);
  Point origin() const;
  Point terminus() const;
  float length() const;
  float angle() const;
private:
  Point mOrigin;
  Point mDragStart;
  Point mDragEnd;
};
}
