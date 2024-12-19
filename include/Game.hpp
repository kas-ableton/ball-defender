#pragma once

#include "EntityManager.hpp"
#include "GameView.hpp"
#include "Point.hpp"

#include <memory>
#include <optional>
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
    StartNewRound,
    LaunchReady,
    BallInMotion,
    BallDead,
    GameOver,
  };

  Game(sf::RenderWindow* window, const std::filesystem::path& resourcesPath);

  void setState(State newState);
  State state() const;

  void handleEvent(const sf::Event& event);

  // @p deltaTimeSec is the amount of time elapsed since the last frame was
  // processed
  void run(float deltaTimeSec);

  unsigned int score() const;

private:
  enum State mState = State::Unstarted;

  GameView mGameView;
  EntityManager mEntityManager;

  std::optional<Point> mLaunchStart;
  Point mLaunchEnd;
};
} // namespace bd
