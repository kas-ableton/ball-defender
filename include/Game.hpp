#include "Ball.hpp"

#include <memory>
#include <vector>

namespace sf {
class Drawable;
class Event;
class CircleShape;
class RectangleShape;
class RenderWindow;
} // namespace sf


namespace bd {
class Game {
public:
  enum class State {
    Unstarted,
    LaunchReady,
  };

  Game(sf::RenderWindow* window);

  void draw();

  void handleEvent(const sf::Event& event);

  void run();

  void start();

  State state() const;

private:
  std::vector<sf::Drawable*> mDrawObjects;
  std::unique_ptr<sf::CircleShape> mpBall;
  std::unique_ptr<sf::RectangleShape> mpPlayArea;
  sf::RenderWindow* mpWindow;
  int mScore = 0;
  enum State mState;
};
} // namespace bd
