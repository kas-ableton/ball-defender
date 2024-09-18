#include "GameModel.hpp"
#include "Constants.hpp"
#include "Point.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

namespace bd {

struct Point;

GameModel::GameModel(Point&& ballStartPos)
    : mBallPosition(std::move(ballStartPos)) {}

void GameModel::updateBallPosition() {
  if (state() == State::BallInMotion) {
    if (mBallLaunch.yDisplacement != std::numeric_limits<float>::min()) {
      mState = bd::GameModel::State::BallDead;
    }

    auto newXPos =
        mBallPosition.x() + (mBallLaunch.xDisplacement * bd::kVelocity);
    auto newYPos =
        mBallPosition.y() + mBallLaunch.yDisplacement * bd::kVelocity;

    mInternalBallPosX =
        std::clamp(newXPos, 0.0f, static_cast<float>(kPlayAreaX));
    mInternalBallPosY =
        std::clamp(newYPos, 0.0f, static_cast<float>(kPlayAreaY));

    mBallPosition.setX(static_cast<int>(mInternalBallPosX));
    mBallPosition.setY(static_cast<int>(mInternalBallPosY));
  }
}

Point GameModel::ballPosition() const { return mBallPosition; }

void GameModel::onLaunchEnd(Point&& endPos) {
  // save release point of launch
  mBallLaunch.endPos = endPos;

  // misfire
  if (mBallLaunch.endPos == mBallLaunch.startPos) {
    return;
  }

  int xMove = mBallLaunch.endPos.x() - mBallLaunch.startPos.x();
  int yMove = mBallLaunch.endPos.y() - mBallLaunch.startPos.y();

  auto r = std::sqrt(xMove * xMove + yMove * yMove);
  // get normalized values of x and y
  mBallLaunch.yDisplacement = yMove / r;
  mBallLaunch.xDisplacement = xMove / r;
}

void GameModel::onLaunchStart(Point&& startPos) {
  mBallLaunch.startPos = startPos;
}

void GameModel::setState(State newState) { mState = newState; }

auto GameModel::state() const -> State { return mState; }

void GameModel::resetScore() { mScore = 0; };

int GameModel::score() const { return mScore; }

} // namespace bd
