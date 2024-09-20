#pragma once

#include "PointSubject.hpp"

#include <limits>

namespace bd {

class Launch {
public:
  float xDisplacement = std::numeric_limits<float>::min();
  float yDisplacement = std::numeric_limits<float>::min();
  Point startPos;
  Point endPos;
};

class GameModel {
public:
  enum class State {
    Unstarted,
    LaunchReady,
    BallInMotion,
    BallDead,
  };

  GameModel(Point&& ballStartPos);

  void onBallPositionChanged();
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
  float mInternalBallPosX;
  float mInternalBallPosY;
  PointSubject mBallPosition;
  int mScore = 0;
  enum State mState = State::Unstarted;
};
} // namespace bd
