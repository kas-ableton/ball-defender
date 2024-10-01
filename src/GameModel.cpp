#include "GameModel.hpp"

#include <algorithm>
#include <functional>
#include <iostream>

#include "Constants.hpp"
#include "Point.hpp"

namespace bd {

struct Point;

void GameModel::setState(State newState) {
  mState = newState;

  switch (mState) {
  case State::Unstarted:
    break;
  case State::LaunchReady:
    break;
  case State::BallInMotion:
    break;
  case State::BallDead:
    break;
  case State::GameOver:
    break;
  }

  emitEvent(Event::StateChanged);
}

auto GameModel::state() const -> State { return mState; }

void GameModel::emitEvent(Event&& event) {
  for (auto callback : mReceiverCallbacks) {
    callback(event);
  }
}

} // namespace bd
