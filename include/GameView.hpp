#pragma once

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <vector>

namespace sf {
class Drawable;
class RenderWindow;
} // namespace sf

namespace bd {
struct Block;
using Blocks = std::vector<Block>;
class Game;
class EntityManager;
class Point;

const std::string kFontFile = "Courier New Bold.ttf";

struct DrawObject {
  DrawObject(std::unique_ptr<sf::Drawable>&& pDrawable,
             std::optional<sf::Transform>&& oTransform)
      : mpDrawable(std::move(pDrawable)), mTransform(std::move(oTransform)) {}
  std::unique_ptr<sf::Drawable> mpDrawable;
  std::optional<sf::Transform> mTransform;
};

class GameView {
public:
  GameView(sf::RenderWindow* window, Game* pGame, EntityManager* pEntityManager,
           const std::filesystem::path& resourcesPath);

  void addDrawObject(std::unique_ptr<sf::Drawable> object);
  void addDrawObject(DrawObject&& object);
  void addBallToDrawObjects(const Point& position);
  void addPlayAreaToDrawObjects();
  void addBlocksToDrawObjects(const Blocks& blocks);
  void addScoreToDrawObjects(unsigned int score);
  void addGameOverTextToDrawObjects();
  void addStartScreenToDrawObjects();

  float scaleSize() const;

  void draw();

private:
  void reset();

  sf::RenderWindow* mpWindow;
  sf::Font mFont;

  float mSizeScale = 1.0f;

  Game* mpGame;
  EntityManager* mpEntityManager;

  std::vector<DrawObject> mDrawObjects;

  std::unique_ptr<sf::CircleShape> mpBall;
  std::unique_ptr<sf::RectangleShape> mpPlayArea;
};

} // namespace bd
