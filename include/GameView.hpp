#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace sf {
class Drawable;
class RenderWindow;
} // namespace sf

namespace bd {
class Game;
class EntityManager;

class GameView {
public:
  GameView(sf::RenderWindow* window, Game* pGame,
           EntityManager* pEntityManager);

  void addDrawObject(std::unique_ptr<sf::Drawable> object);
  void addBallToDrawObjects(int x, int y);
  void addPlayAreaToDrawObjects();
  void addBlocksToDrawObjects();

  void draw();

private:
  void reset();

  sf::RenderWindow* mpWindow;

  Game* mpGame;
  EntityManager* mpEntityManager;

  std::vector<std::unique_ptr<sf::Drawable>> mDrawObjects;

  std::unique_ptr<sf::CircleShape> mpBall;
  std::unique_ptr<sf::RectangleShape> mpPlayArea;
};

} // namespace bd
