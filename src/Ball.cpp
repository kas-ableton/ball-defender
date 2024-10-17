#include "Ball.hpp"

#include "Constants.hpp"

#include <algorithm>
#include <memory>

namespace bd {
Ball::Ball(Point&& ballStartPos)
    : mLaunchPosition(std::move(ballStartPos)), mPosition(mLaunchPosition),
      mInternalBallPosX(mPosition.x()), mInternalBallPosY(mPosition.y()) {}

Point Ball::position() const { return mPosition; }

void Ball::reflect(Vector::Axis axis) {
  mVector.reflect(axis);
}

void Ball::onLaunch(Point&& startPos, Point&& endPos) {
  mVector = Vector{std::move(startPos), std::move(endPos)};
}

void Ball::update() {
  auto newXPos = mInternalBallPosX + (mVector.xDelta * bd::kVelocity);
  auto newYPos = mInternalBallPosY + mVector.yDelta * bd::kVelocity;

  mInternalBallPosX = std::clamp(newXPos, static_cast<float>(kWindowPadding), static_cast<float>(kPlayAreaX));
  mInternalBallPosY = std::clamp(newYPos, static_cast<float>(kWindowPadding), static_cast<float>(kPlayAreaY));

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
