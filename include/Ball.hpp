#pragma once

#include "Entity.hpp"
#include "Point.hpp"
#include "Vector.hpp"

namespace bd {
class Ball {
public:
  Ball(Point&& ballStartPos);
  Point position() const;
  void reflect(Vector::Axis axis);
  void onLaunch(Point&& startPos, Point&& endPos);
  void update();
  void reset();

private:
  Vector mVector;
  Point mLaunchPosition;
  Point mPosition;
  float mInternalBallPosX;
  float mInternalBallPosY;
};
} // namespace bd
