#include "GameView.hpp"
#include "Constants.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

namespace bd {

GameView::GameView(sf::RenderWindow* window, GameModel* gameModel)
    : mpWindow(window), mpGameModel(gameModel) {}

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

void GameView::addBallToDrawObjects(int x, int y) {
  auto pBall = std::make_unique<sf::CircleShape>(kBallRadius);

  pBall->setFillColor(sf::Color(250, 250, 250));
  pBall->setPosition(x, y);

  addDrawObject(std::move(pBall));
}

void GameView::draw() {
  reset();

  if (mpGameModel->state() != bd::GameModel::State::Unstarted) {
      addPlayAreaToDrawObjects();
  }

  if (mpGameModel->state() == bd::GameModel::State::BallInMotion) {
    addBallToDrawObjects(mpGameModel->ballPosition().x(),
                         mpGameModel->ballPosition().y());
  }

  for (const auto& obj : mDrawObjects) {
    mpWindow->draw(*obj);
  }
}

void GameView::handleState() {
  switch (mpGameModel->state()) {
  case GameModel::State::Unstarted:
    reset();
    break;
  case GameModel::State::LaunchReady:
    launchReadyState();
    break;
  case GameModel::State::BallInMotion:
    // add observer to GameModel::ballPosition()
    break;
  case GameModel::State::BallDead:
    break;
  default:
    break;
  }
}

void GameView::launchReadyState() {
  reset();
  addPlayAreaToDrawObjects();
  addBallToDrawObjects(bd::kBallStartPosX, bd::kBallStartPosY);
}

void GameView::reset() { mDrawObjects.clear(); }

} // namespace bd
