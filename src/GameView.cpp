#include "GameView.hpp"
#include "Constants.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace bd {

GameView::GameView(sf::RenderWindow* window, GameModel* gameModel)
    : mpWindow(window), mpGameModel(gameModel) {}

void GameView::addDrawObject(sf::Drawable* object) {
  mDrawObjects.push_back(object);
}

void GameView::draw() {
  mpWindow->clear();

  for (const auto& obj : mDrawObjects) {
    mpWindow->draw(*obj);
  }

  mpWindow->display();
}

void GameView::handleState() {
  switch (mpGameModel->state()) {
  case GameModel::State::Unstarted:
    reset();
  case GameModel::State::LaunchReady:
    launchReadyState();
  case GameModel::State::BallInMotion:
    // add observer to GameModel::ballPosition()
  case GameModel::State::BallDead:
  default:
    reset();
  }
}

void GameView::launchReadyState() {
  reset();

  mpPlayArea = std::make_unique<sf::RectangleShape>(
      sf::Vector2f(bd::kPlayAreaX, bd::kPlayAreaY));
  mpPlayArea->setFillColor(sf::Color(100, 250, 50));
  mpPlayArea->setPosition(bd::kWindowPadding, bd::kWindowPadding);

  addDrawObject(mpPlayArea.get());

  // TODO draw blocks

  mpBall = std::make_unique<sf::CircleShape>(kBallRadius);
  mpBall->setFillColor(sf::Color(250, 250, 250));
  mpBall->setPosition(bd::kWindowPadding + mpPlayArea->getSize().x / 2,
                      mpPlayArea->getSize().y);

  addDrawObject(mpBall.get());
}

void GameView::reset() { mDrawObjects.clear(); }

} // namespace bd
