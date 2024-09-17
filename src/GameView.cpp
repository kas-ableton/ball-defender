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
  // Temporary solution until observer pattern set up
  if (mpGameModel->state() == bd::GameModel::State::BallInMotion) {
    mpBall->setPosition(mpGameModel->ballPosition().x(),
                        mpGameModel->ballPosition().y());
  }

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

  mpPlayArea = std::make_unique<sf::RectangleShape>(
      sf::Vector2f(bd::kPlayAreaX, bd::kPlayAreaY));
  mpPlayArea->setFillColor(sf::Color(100, 250, 50));
  mpPlayArea->setPosition(bd::kWindowPadding, bd::kWindowPadding);

  addDrawObject(mpPlayArea.get());

  // TODO draw blocks

  mpBall = std::make_unique<sf::CircleShape>(kBallRadius);
  mpBall->setFillColor(sf::Color(250, 250, 250));
  mpBall->setPosition(bd::kBallStartPosX, bd::kBallStartPosY);

  addDrawObject(mpBall.get());
}

void GameView::reset() { mDrawObjects.clear(); }

} // namespace bd
