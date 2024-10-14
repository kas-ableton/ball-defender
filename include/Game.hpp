#pragma once

#include "EntityManager.hpp"
#include "GameView.hpp"
#include "Point.hpp"

#include <memory>
#include <vector>

namespace sf {
class Event;
class RenderWindow;
} // namespace sf

namespace bd {
class Game {
public:
  enum class State {
    Unstarted,
    LaunchReady,
    BallInMotion,
    BallDead,
    GameOver,
  };

  Game(sf::RenderWindow* window, const std::filesystem::path& resourcesPath);

  void setState(State newState);
  State state() const;

  void handleEvent(const sf::Event& event);

  void run();

  void start();

  unsigned int score() const;

private:
  enum State mState = State::Unstarted;

  GameView mGameView;
  EntityManager mEntityManager;

  Point mLaunchStart;
};
} // namespace bd
