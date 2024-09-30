#pragma once

#include "Ball.hpp"
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
    GameOver,
  };

  enum class Event {
    StateChanged,
  };

  template <typename Class>
  void registerReceiver(Class* pClass, void(const Class*, const Event& event));

  void resetScore();
  int score() const;

  void setState(State newState);
  State state() const;

private:
  void emitEvent(Event&& event);
  std::vector<void(*)(const Event&)> mReceiverCallbacks;

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
