#include "Ball.hpp"

#include <algorithm>
#include <iostream>
#include <memory>

namespace bd {

// pixels per second
constexpr float kVelocity = 1440.0f;

Ball::Ball(Point&& ballStartPos, float MaxXPos, float MaxYPos)
    : mMaxXPos(MaxXPos), mMaxYPos(MaxYPos),
      mLaunchPosition(std::move(ballStartPos)), mPosition(mLaunchPosition),
      mInternalBallPosX(mPosition.x()), mInternalBallPosY(mPosition.y()) {}

Point Ball::position() const { return mPosition; }

void Ball::setVector(const Vector& newVector) { mVector = newVector; }

const Vector& Ball::vector() const { return mVector; }

void Ball::onLaunch(Point&& startPos, Point&& endPos) {
  mVector = Vector{std::move(startPos), std::move(endPos)};
}

void Ball::update(float deltaTimeSec) {
  auto newXPos = mInternalBallPosX + (mVector.x * deltaTimeSec * kVelocity);
  auto newYPos = mInternalBallPosY + mVector.y * deltaTimeSec * kVelocity;

  mInternalBallPosX = std::clamp(newXPos, 0.0f, static_cast<float>(mMaxXPos));
  mInternalBallPosY = std::clamp(newYPos, 0.0f, static_cast<float>(mMaxYPos));

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
