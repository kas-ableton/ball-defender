#include "Ball.hpp"

#include "Constants.hpp"

#include <algorithm>
#include <memory>

namespace bd {
Ball::Ball(Point&& ballStartPos)
    : mLaunchPosition(std::move(ballStartPos)), mPosition(mLaunchPosition),
      mInternalBallPosX(mPosition.x()), mInternalBallPosY(mPosition.y()) {}

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

  if (mPosition.x() == kPlayAreaX || mPosition.x() == 0) {
    mVector.reflect(Vector::Axis::Y);
  }

  if (mPosition.y() == 0) {
    mVector.reflect(Vector::Axis::X);
  }
}

void Ball::resetLaunchPosition() {
  mVector.reset();
  mPosition = mLaunchPosition;
  mInternalBallPosX = mPosition.x();
  mInternalBallPosY = mPosition.y();
}

} // namespace bd
