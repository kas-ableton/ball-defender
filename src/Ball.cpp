#include "Ball.hpp"

#include "Constants.hpp"

#include <algorithm>
#include <memory>
#include <iostream>

namespace bd {
Ball::Ball(Point&& ballStartPos)
    : mLaunchPosition(std::move(ballStartPos)), mPosition(mLaunchPosition),
      mInternalBallPosX(mPosition.x()), mInternalBallPosY(mPosition.y()) {}

Point Ball::position() const { return mPosition; }

void Ball::setVector(const Vector& newVector) {
  mVector = newVector;
}

const Vector& Ball::vector() const {
  return mVector;
}

void Ball::onLaunch(Point&& startPos, Point&& endPos) {
  mVector = Vector{std::move(startPos), std::move(endPos)};
}

void Ball::update(float deltaTimeSec) {
  auto newXPos = mInternalBallPosX + (mVector.x * deltaTimeSec * bd::kVelocity);
  auto newYPos = mInternalBallPosY + mVector.y * deltaTimeSec * bd::kVelocity;

  mInternalBallPosX = std::clamp(newXPos, 0.0f, static_cast<float>(kPlayAreaX));
  mInternalBallPosY = std::clamp(newYPos, 0.0f, static_cast<float>(kPlayAreaY));

  mPosition.setX(static_cast<int>(mInternalBallPosX));
  mPosition.setY(static_cast<int>(mInternalBallPosY));
}

void Ball::reset() {
  mVector.reset();
  // we assume reset is called after the ball last exited the play area
  // so, only reset the y-position. The x-position is already correct.
  mPosition.setY(mLaunchPosition.y());
  mInternalBallPosX = mPosition.x();
  mInternalBallPosY = mPosition.y();
}

} // namespace bd
