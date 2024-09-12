#include "Constants.hpp"
#include "GameModel.hpp"
#include "Point.hpp"

#include <algorithm>
#include <cassert>

namespace bd {

struct Point;

void GameModel::updateBallPosition() {
  if (state() == State::BallInMotion) {
    assert(mBallLaunch.yDisplacement != std::numeric_limits<int>::min());

    auto newXPos = mBallPosition.x + mBallLaunch.xDisplacement;
    auto newYPos = mBallPosition.y + mBallLaunch.yDisplacement;

    mBallPosition.x =
        std::clamp(newXPos, 0, kPlayAreaX);
    mBallPosition.y =
        std::clamp(newYPos, 0, kPlayAreaY);
  }
}

Point GameModel::ballPosition() const { return mBallPosition; }

void GameModel::onLaunchEnd(Point&& endPos) {
  mBallLaunch.endPos = endPos;
  int xMove = mBallLaunch.endPos.x - mBallLaunch.startPos.x;
  int yMove = mBallLaunch.endPos.y - mBallLaunch.startPos.y;
  mBallLaunch.yDisplacement = mBallLaunch.xDisplacement * yMove / xMove;
}

void GameModel::onLaunchStart(Point&& startPos) {
  mBallLaunch.startPos = startPos;
}

void GameModel::setState(State newState) { mState = newState; }

auto GameModel::state() const -> State { return mState; }

void GameModel::resetScore() { mScore = 0; };

int GameModel::score() const { return mScore; }

} // namespace bd
