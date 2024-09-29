#include "Ball.hpp"

#include "Constants.hpp"

#include <algorithm>
#include <memory>

namespace bd {
Ball::Ball(Point&& ballStartPos)
    : mPosition(std::move(ballStartPos)),
      mInternalBallPosX(mPosition.x()),
      mInternalBallPosY(mPosition.y()) {}

Point Ball::position() const { return mPosition; }

void Ball::onLaunch(Point&& startPos, Point&& endPos) {
  mVector = Vector{std::move(startPos), std::move(endPos)};
}

void Ball::update() {
  auto newXPos = mInternalBallPosX + (mVector.xDelta * bd::kVelocity);
  auto newYPos = mInternalBallPosY + mVector.yDelta * bd::kVelocity;

  mInternalBallPosX = std::clamp(newXPos, 0.0f, static_cast<float>(kPlayAreaX));
  mInternalBallPosY = std::clamp(newYPos, 0.0f, static_cast<float>(kPlayAreaY));

  mPosition.setX(static_cast<int>(mInternalBallPosX));
  mPosition.setY(static_cast<int>(mInternalBallPosY));

  // if (auto other = CollisionDetector.check(EntityId::Ball))
  // {
  //    if (other == powerUp)
  //    {
  //        increase velocity
  //    }
  //    else if (other == outOfbounds)
  //    {
  //        reset position+internal to null
  //    }
  //    else if (other.impactSide == Vector::Axis::X)
  //    {
  //        mVector.reflect(Vector::Axis::Y);
  //    }
  //    else if (other.impactSide == Vector::Axis::Y)
  //    {
  //        mVector.reflect(Vector::Axis::X);
  //    }
  // }

  if (mPosition.x() == kPlayAreaX || mPosition.x() == 0) {
    mVector.reflect(Vector::Axis::Y);
  }

  if (mPosition.y() == 0) {
    mVector.reflect(Vector::Axis::X);
  }
}

} // namespace bd
