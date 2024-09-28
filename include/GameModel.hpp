#pragma once

#include "PointSubject.hpp"
#include "Vector.hpp"

namespace bd {

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

  void onBallLaunch(Point&& startPos, Point&& endPos);

  void resetScore();
  int score() const;

  void setState(State newState);
  State state() const;

private:
  Vector mBallVector;
  PointSubject mBallPosition;
  float mInternalBallPosX;
  float mInternalBallPosY;
  int mScore = 0;
  enum State mState = State::Unstarted;
};
} // namespace bd
