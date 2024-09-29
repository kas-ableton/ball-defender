#pragma once

#include "Point.hpp"
#include "Vector.hpp"


namespace bd
{
class Ball
{
public:
  Ball(Point&& ballStartPos);
  Point position() const;
  void onLaunch(Point&& startPos, Point&& endPos);
  void update();
private:
  Vector mVector;
  Point mPosition;
  float mInternalBallPosX;
  float mInternalBallPosY;
};
}
