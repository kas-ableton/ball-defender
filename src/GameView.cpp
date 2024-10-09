#include "GameView.hpp"

#include "Constants.hpp"
#include "EntityManager.hpp"
#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

namespace bd {

GameView::GameView(sf::RenderWindow* window, Game* pGame,
                   EntityManager* pEntityManager)
    : mpWindow(window), mpGame(pGame), mpEntityManager(pEntityManager) {}

void GameView::addDrawObject(std::unique_ptr<sf::Drawable> object) {
  mDrawObjects.emplace_back(std::move(object));
}

void GameView::addPlayAreaToDrawObjects() {
  auto pPlayArea = std::make_unique<sf::RectangleShape>(
      sf::Vector2f(bd::kPlayAreaX, bd::kPlayAreaY));

  pPlayArea->setFillColor(sf::Color(100, 250, 50));
  pPlayArea->setPosition(bd::kWindowPadding, bd::kWindowPadding);

  addDrawObject(std::move(pPlayArea));
}

void GameView::addBlocksToDrawObjects() {
  for (const auto& blockRow : mpEntityManager->blockManager().blocks()) {
    for (const auto& [_, block] : blockRow.blocks()) {
      auto pBlock = std::make_unique<sf::RectangleShape>(
          sf::Vector2f(bd::kBlockSizeX, bd::kBlockSizeY));

      pBlock->setFillColor(sf::Color(250, 250, 250));
      pBlock->setPosition(block.position().x(), block.position().y());

      addDrawObject(std::move(pBlock));
    }
  }
}

void GameView::addBallToDrawObjects(int x, int y) {
  auto pBall = std::make_unique<sf::CircleShape>(kBallRadius);

  pBall->setFillColor(sf::Color(250, 250, 250));
  pBall->setPosition(x, y);

  addDrawObject(std::move(pBall));
}

void GameView::draw() {
  reset();

  if (mpGame->state() != bd::Game::State::Unstarted) {
    addPlayAreaToDrawObjects();
  }

  switch (mpGame->state()) {
  case Game::State::Unstarted:
    // TODO draw start screen
    break;
  case Game::State::LaunchReady:
    addBallToDrawObjects(mpEntityManager->ball().position().x(),
                         mpEntityManager->ball().position().y());
    addBlocksToDrawObjects();
    break;
  case Game::State::BallInMotion:
    addBallToDrawObjects(mpEntityManager->ball().position().x(),
                         mpEntityManager->ball().position().y());
    addBlocksToDrawObjects();
    break;
  case Game::State::BallDead:
    addBlocksToDrawObjects();
    break;
  default:
    break;
  }

  for (const auto& obj : mDrawObjects) {
    mpWindow->draw(*obj);
  }
}

void GameView::reset() { mDrawObjects.clear(); }

} // namespace bd
