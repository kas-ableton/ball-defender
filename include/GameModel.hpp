#pragma once

#include "Point.hpp"

#include <limits>

namespace bd {

namespace {
class Launch {
public:
  static const int xDisplacement = 2;
  int yDisplacement = std::numeric_limits<int>::min();
  Point startPos;
  Point endPos;
};
} // namespace

class GameModel {
public:
  enum class State {
    Unstarted,
    LaunchReady,
    BallInMotion,
    BallDead,
  };

  void updateBallPosition();
  Point ballPosition() const;

  void onLaunchEnd(Point&& endPos);
  void onLaunchStart(Point&& startPos);

  void resetScore();
  int score() const;

  void setState(State newState);
  State state() const;

private:
  Launch mBallLaunch;
  Point mBallPosition;
  int mScore = 0;
  enum State mState = State::Unstarted;
};
} // namespace bd
