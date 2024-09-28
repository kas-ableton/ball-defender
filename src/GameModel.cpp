#include "GameModel.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

#include "Constants.hpp"
#include "Point.hpp"

namespace bd {

struct Point;

GameModel::GameModel(Point&& ballStartPos)
    : mBallPosition(std::move(ballStartPos)),
      mInternalBallPosX(ballStartPos.x()), mInternalBallPosY(ballStartPos.y()) {
}

void GameModel::updateBallVector() {
  if (mBallPosition.x() == kPlayAreaX || mBallPosition.x() == 0) {
    mBallVector.reflect(Vector::Axis::Y);
  }

  if (mBallPosition.y() == 0) {
    mBallVector.reflect(Vector::Axis::X);
  }

  if (mBallPosition.y() == kPlayAreaY) {
    setState(State::BallDead);
  }
}

void GameModel::updateBallPosition() {
  if (state() == State::BallInMotion) {
    auto newXPos = mInternalBallPosX + (mBallVector.xDelta * bd::kVelocity);
    auto newYPos = mInternalBallPosY + mBallVector.yDelta * bd::kVelocity;

    mInternalBallPosX =
        std::clamp(newXPos, 0.0f, static_cast<float>(kPlayAreaX));
    mInternalBallPosY =
        std::clamp(newYPos, 0.0f, static_cast<float>(kPlayAreaY));

    mBallPosition.setX(static_cast<int>(mInternalBallPosX));
    mBallPosition.setY(static_cast<int>(mInternalBallPosY));

    updateBallVector();
  }
}

void GameModel::onBallPositionChanged() {
  // check for collisions
  // update mBallLaunch
  // change state when ball is dead
  // etc
}

Point GameModel::ballPosition() const { return mBallPosition; }

void GameModel::onBallLaunch(Point&& startPos, Point&& endPos) {
  mBallVector = Vector{std::move(startPos), std::move(endPos)};
}

void GameModel::setState(State newState) { mState = newState; }

auto GameModel::state() const -> State { return mState; }

void GameModel::resetScore() { mScore = 0; };

int GameModel::score() const { return mScore; }

} // namespace bd
