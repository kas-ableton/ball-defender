#pragma once


namespace bd {
class GameModel {
public:
  enum class State {
    Unstarted,
    LaunchReady,
  };

  void resetScore();
  int score() const;

  void setState(State newState);
  State state() const;

private:
  int mScore = 0;
  enum State mState = State::Unstarted;
};
} // namespace bd
