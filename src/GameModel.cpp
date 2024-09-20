#include "GameModel.hpp"
#include "Constants.hpp"
#include "Point.hpp"

#include <algorithm>
#include <functional>
#include <cmath>
#include <iostream>

namespace bd {

struct Point;

GameModel::GameModel(Point&& ballStartPos)
    : mBallPosition(std::move(ballStartPos)),
    mInternalBallPosX(ballStartPos.x()),
    mInternalBallPosY(ballStartPos.y())
{
  //mBallPosition.addObserver();
}

void GameModel::updateBallPosition() {
  if (state() == State::BallInMotion) {

    auto newXPos =
        mInternalBallPosX + (mBallLaunch.xDisplacement * bd::kVelocity);
    auto newYPos =
        mInternalBallPosY + mBallLaunch.yDisplacement * bd::kVelocity;

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
  std::cout << mBallPosition.x() << ',' <<mBallPosition.y() << '\n';
  // check for collisions
  // update mBallLaunch
  // change state when ball is dead
  // etc
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

  // length of the vector
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
