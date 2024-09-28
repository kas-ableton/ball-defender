#pragma once

#include "GameModel.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace sf {
class Drawable;
class RenderWindow;
} // namespace sf

namespace bd {
class GameModel;

class GameView {
public:
  GameView(sf::RenderWindow* window, GameModel* gameModel);

  void addDrawObject(std::unique_ptr<sf::Drawable> object);
  void addBallToDrawObjects(int x, int y);
  void addPlayAreaToDrawObjects();

  void draw();

  void handleState();

  void launchReadyState();

  void onBallPositionChanged(const Point& newPos);

private:
  void reset();

  sf::RenderWindow* mpWindow;

  GameModel* mpGameModel;

  std::vector<std::unique_ptr<sf::Drawable>> mDrawObjects;

  std::unique_ptr<sf::CircleShape> mpBall;
  std::unique_ptr<sf::RectangleShape> mpPlayArea;
};

} // namespace bd
