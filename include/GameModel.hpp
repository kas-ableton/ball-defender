#pragma once

#include "PointSubject.hpp"
#include "Vector.hpp"

#include <functional>
#include <vector>

namespace bd {

class GameModel {
public:
  enum class State {
    Unstarted,
    LaunchReady,
    BallInMotion,
    BallDead,
  };

  enum class Event {
    StateChanged,
  };

  GameModel(Point&& ballStartPos);

  template <typename Class>
  void registerReceiver(Class* pClass, void(const Class*, const Event& event));

  void onBallPositionChanged();
  void updateBallVector();
  void updateBallPosition();
  Point ballPosition() const;

  void onBallLaunch(Point&& startPos, Point&& endPos);

  void resetScore();
  int score() const;

  void setState(State newState);
  State state() const;

private:
  void emitEvent(Event&& event);
  std::vector<void(*)(const Event&)> mReceiverCallbacks;

  Vector mBallVector;
  PointSubject mBallPosition;
  float mInternalBallPosX;
  float mInternalBallPosY;
  int mScore = 0;
  enum State mState = State::Unstarted;
};

template <typename Class>
void GameModel::registerReceiver(Class* pClass,
                                 void (*pFunc)(const Class*,
                                               const Event& event)) {
  mReceiverCallbacks.push_back(std::bind(pFunc, pClass, std::placeholders::_1));
}

} // namespace bd
