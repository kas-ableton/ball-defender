#include "GameModel.hpp"
#include "Constants.hpp"
#include "Point.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

namespace bd {

struct Point;

GameModel::GameModel(Point&& ballStartPos)
    : mBallPosition(std::move(ballStartPos)),
      mInternalBallPosX(ballStartPos.x()), mInternalBallPosY(ballStartPos.y()) {
}

void GameModel::updateBallPosition() {
  if (state() == State::BallInMotion) {

    auto newXPos = mInternalBallPosX + (mBallVector.xDelta * bd::kVelocity);
    auto newYPos = mInternalBallPosY + mBallVector.yDelta * bd::kVelocity;

    mInternalBallPosX =
        std::clamp(newXPos, 0.0f, static_cast<float>(kPlayAreaX));
    mInternalBallPosY =
        std::clamp(newYPos, 0.0f, static_cast<float>(kPlayAreaY));

    std::cout << 'f' << mInternalBallPosX << ',';
    std::cout << mInternalBallPosY << '\n';

    mBallPosition.setX(static_cast<int>(mInternalBallPosX));
    mBallPosition.setY(static_cast<int>(mInternalBallPosY));
  }
}

void GameModel::onBallPositionChanged() {
  std::cout << mBallPosition.x() << ',' << mBallPosition.y() << '\n';
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
