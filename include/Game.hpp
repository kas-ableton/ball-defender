namespace sf
{
class RenderWindow;
}

namespace bd
{
class Game {
public:
  enum class State {
    Unstarted,
    LaunchReady,
  };

  Game(sf::RenderWindow* window);

  void Start();

  State State() const;

private:
  sf::RenderWindow* mWindow;
  int mScore = 0;
  enum State mState;
};
}
