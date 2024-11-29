#include "GameView.hpp"

#include "Constants.hpp"
#include "EntityManager.hpp"
#include "Game.hpp"
#include "LaunchRay.hpp"
#include "Point.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>

namespace bd {

GameView::GameView(sf::RenderWindow* window, Game* pGame,
                   EntityManager* pEntityManager,
                   const std::filesystem::path& resourcesPath)
    : mpWindow(window), mpGame(pGame), mpEntityManager(pEntityManager) {
  mFont.loadFromFile(resourcesPath / kFontFile);
  mSizeScale = mpWindow->getSize().y / static_cast<float>(kWindowSizeY);
}

void GameView::addDrawObject(std::unique_ptr<sf::Drawable>&& pDrawable,
                             std::optional<sf::Transform>&& oTransform) {
  mDrawObjects.emplace_back(std::move(pDrawable), std::move(oTransform));
}

void GameView::addDrawObject(std::unique_ptr<sf::Drawable> object) {
  mDrawObjects.emplace_back(std::move(object), std::nullopt);
}

void GameView::addPlayAreaToDrawObjects() {
  auto pPlayArea = std::make_unique<sf::RectangleShape>(
      sf::Vector2f(bd::kPlayAreaX, bd::kPlayAreaY));

  pPlayArea->setFillColor(sf::Color(100, 250, 50));
  pPlayArea->setPosition(0.0f, 0.0f);

  addDrawObject(std::move(pPlayArea));
}

void GameView::addBlocksToDrawObjects(const Blocks& blocks) {
  for (const auto& block : blocks) {
    auto pBlock = std::make_unique<sf::RectangleShape>(
        sf::Vector2f(bd::kBlockSizeX, bd::kBlockSizeY));

    pBlock->setFillColor(sf::Color(250, 250, 250));
    pBlock->setPosition(block.position.x(), block.position.y());

    auto pHitCountText = std::make_unique<sf::Text>();
    pHitCountText->setFont(mFont);
    pHitCountText->setString(std::to_string(block.hitCount));
    pHitCountText->setCharacterSize(bd::kBlockHitCountTextSize);
    pHitCountText->setFillColor(sf::Color::Red);

    const auto textSize = pHitCountText->getLocalBounds();
    const auto blockPos = pBlock->getPosition();
    pHitCountText->setPosition(
        blockPos.x + ((bd::kBlockSizeX - static_cast<int>(textSize.width)) / 2),
        blockPos.y + ((bd::kBlockSizeY - bd::kBlockHitCountTextSize) / 2));

    addDrawObject(std::move(pBlock));
    addDrawObject(std::move(pHitCountText));
  }
}

void GameView::addBallToDrawObjects(const Point& position) {
  auto pBall = std::make_unique<sf::CircleShape>(kBallRadius);

  pBall->setFillColor(sf::Color(250, 250, 250));
  pBall->setPosition(position.x(), position.y());

  addDrawObject(std::move(pBall));
}

void GameView::addScoreToDrawObjects(unsigned int score) {
  auto pScoreText = std::make_unique<sf::Text>();

  static const unsigned int characterSize = 50;

  pScoreText->setFont(mFont);
  pScoreText->setString(std::to_string(score));
  pScoreText->setCharacterSize(characterSize);
  pScoreText->setFillColor(sf::Color(100, 250, 50));
  // TODO think about how to do this...
  pScoreText->setPosition(bd::kPlayAreaX + (2 * bd::kWindowPadding), 0);

  addDrawObject(std::move(pScoreText));
}

void GameView::addGameOverTextToDrawObjects() {
  auto pGameOverText = std::make_unique<sf::Text>();

  pGameOverText->setFont(mFont);
  pGameOverText->setString("Game over!");
  pGameOverText->setCharacterSize(50);
  pGameOverText->setPosition(bd::kWindowSizeX / 2, bd::kWindowSizeY / 2);

  addDrawObject(std::move(pGameOverText));
}

void GameView::addStartScreenToDrawObjects() {
  auto pStartText = std::make_unique<sf::Text>();

  pStartText->setFont(mFont);
  pStartText->setString("Click anywhere to start");
  pStartText->setCharacterSize(30);
  pStartText->setPosition(bd::kWindowSizeX - bd::kPlayAreaX,
                          bd::kWindowSizeY / 2);

  addDrawObject(std::move(pStartText));
}

void GameView::addLaunchRayToDrawObjects(const LaunchRay& ray) {
  const auto origin = ray.origin();

  auto pRayRect = std::make_unique<sf::RectangleShape>(
      sf::Vector2f(bd::kLaunchRayWidth, ray.length()));
  pRayRect->setFillColor(sf::Color::Blue);
  pRayRect->setPosition(origin.x(), origin.y());
  pRayRect->rotate(ray.angle() + 90.0f);
  addDrawObject(std::move(pRayRect));
}

float GameView::scaleSize() const { return mSizeScale; }

void GameView::draw() {
  reset();

  if (mpGame->state() != bd::Game::State::Unstarted) {
    addPlayAreaToDrawObjects();
    addScoreToDrawObjects(mpGame->score());
  }

  switch (mpGame->state()) {
  case Game::State::Unstarted:
    addStartScreenToDrawObjects();
    break;
  case Game::State::LaunchReady:
    addBlocksToDrawObjects(mpEntityManager->blockManager().blocks());
    if (auto oLaunchRay = mpEntityManager->launchRay()) {
      addLaunchRayToDrawObjects(*oLaunchRay);
    }
    addBallToDrawObjects(mpEntityManager->ball().position());
    break;
  case Game::State::BallInMotion:
    addBallToDrawObjects(mpEntityManager->ball().position());
    addBlocksToDrawObjects(mpEntityManager->blockManager().blocks());
    break;
  case Game::State::BallDead:
    addBlocksToDrawObjects(mpEntityManager->blockManager().blocks());
    break;
  case Game::State::GameOver:
    addBlocksToDrawObjects(mpEntityManager->blockManager().blocks());
    addGameOverTextToDrawObjects();
    break;
  default:
    break;
  }

  sf::Transform BaseTransform;
  auto paddingAmount = bd::kWindowPadding * mSizeScale;
  BaseTransform.translate(paddingAmount, paddingAmount);
  BaseTransform.scale(mSizeScale, mSizeScale);

  for (auto& obj : mDrawObjects) {
    auto& [pObj, oTransform] = obj;
    auto Transform =
        oTransform ? oTransform->combine(BaseTransform) : BaseTransform;
    mpWindow->draw(*pObj, Transform);
  }
}

void GameView::reset() { mDrawObjects.clear(); }

} // namespace bd
