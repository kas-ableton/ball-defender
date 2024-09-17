#include "GameModel.hpp"
#include "Constants.hpp"
#include "Point.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace bd {

struct Point;

GameModel::GameModel(Point&& ballStartPos)
    : mBallPosition(std::move(ballStartPos)) {}

void GameModel::updateBallPosition() {
  if (state() == State::BallInMotion) {
    assert(mBallLaunch.yDisplacement != std::numeric_limits<float>::min());

    auto newXPos = mBallPosition.x() +
                   (mBallLaunch.xDisplacement * mBallLaunch.xDirection);
    auto newYPos = mBallPosition.y() + mBallLaunch.yDisplacement;

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
    mBallLaunch.yDisplacement = 0.0f;
  }

  // save if launch was left or right
  mBallLaunch.xDirection =
      mBallLaunch.endPos.x() > mBallLaunch.startPos.x() ? 1 : -1;

  int xMove = mBallLaunch.endPos.x() - mBallLaunch.startPos.x();
  int yMove = mBallLaunch.endPos.y() - mBallLaunch.startPos.y();

  // avoid division by zero
  if (xMove == 0) {
    mBallLaunch.yDisplacement = mBallLaunch.xDisplacement;
    mBallLaunch.xDisplacement = 0.0;
    return;
  }

  // calculate how much ball will move in the y-direction on every update
  mBallLaunch.yDisplacement =
      mBallLaunch.xDisplacement * mBallLaunch.xDirection * yMove / xMove;
}

void GameModel::onLaunchStart(Point&& startPos) {
  mBallLaunch.startPos = startPos;
}

void GameModel::setState(State newState) { mState = newState; }

auto GameModel::state() const -> State { return mState; }

void GameModel::resetScore() { mScore = 0; };

int GameModel::score() const { return mScore; }

} // namespace bd
