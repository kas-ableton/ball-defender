#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace sf {
class Drawable;
class RenderWindow;
} // namespace sf

namespace bd {

class GameView {
public:
  GameView(sf::RenderWindow* window);

  void addDrawObject(sf::Drawable*);

  void draw();

  void setup();

private:
  std::vector<sf::Drawable*> mDrawObjects;
  sf::RenderWindow* mpWindow;

  std::unique_ptr<sf::CircleShape> mpBall;
  std::unique_ptr<sf::RectangleShape> mpPlayArea;
};

} // namespace bd
