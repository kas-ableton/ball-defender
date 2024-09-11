#pragma once

#include "GameView.hpp"
#include "GameModel.hpp"

#include <memory>
#include <vector>

namespace sf {
class Event;
class RenderWindow;
} // namespace sf


namespace bd {
class Game {
public:
  Game(sf::RenderWindow* window);

  void handleEvent(const sf::Event& event);

  void run();

  void start();

private:
  GameView mGameView;
  GameModel mGameModel;
};
} // namespace bd
