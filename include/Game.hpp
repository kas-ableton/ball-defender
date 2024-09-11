#include "GameView.hpp"

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
  };

  Game(sf::RenderWindow* window);

  void handleEvent(const sf::Event& event);

  void run();

  void start();

  State state() const;

private:
  GameView mGameView;
  int mScore = 0;
  enum State mState;
};
} // namespace bd
