#pragma once

#include "Entity.hpp"
#include "Point.hpp"
#include "Vector.hpp"

namespace bd {
class Ball {
public:
  Ball(Point&& ballStartPos, float MaxXPos, float MaxYPos);
  Point position() const;
  const Vector& vector() const;
  void setVector(const Vector& newVector);
  void onLaunch(Point&& startPos, Point&& endPos);
  void update(float deltaTimeSec);
  void reset();

private:
  float mMaxXPos;
  float mMaxYPos;
  Vector mVector;
  Point mLaunchPosition;
  Point mPosition;
  float mInternalBallPosX;
  float mInternalBallPosY;
};
} // namespace bd
