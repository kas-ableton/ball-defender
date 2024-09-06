#include "Game.hpp"
#include "Constants.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace bd {

Game::Game(sf::RenderWindow* window) : mpWindow(window) {}

void Game::draw() {
  mpWindow->clear();

  for (const auto& obj : mDrawObjects) {
    mpWindow->draw(*obj);
  }

  mpWindow->display();
}

void Game::handleEvent(const sf::Event& event) {
  if (mState == bd::Game::State::Unstarted) {
    if (event.type == sf::Event::MouseButtonReleased) {
      start();
    }
  } else if (mState == bd::Game::State::LaunchReady) {
    if (event.type == sf::Event::MouseButtonReleased) {
    }
  }
}

void Game::run() {}

void Game::start() {
  mState = State::LaunchReady;

  mScore = 0;

  mpPlayArea = std::make_unique<sf::RectangleShape>(
      sf::Vector2f(bd::kPlayAreaX, bd::kPlayAreaY));
  mpPlayArea->setFillColor(sf::Color(100, 250, 50));
  mpPlayArea->setPosition(bd::kWindowPadding, bd::kWindowPadding);

  mDrawObjects.push_back(mpPlayArea.get());

  mpBall = std::make_unique<sf::CircleShape>(kBallRadius);
  mpBall->setFillColor(sf::Color(250, 250, 250));
  mpBall->setPosition(bd::kWindowPadding + mpPlayArea->getSize().x / 2,
                      mpPlayArea->getSize().y);

  mDrawObjects.push_back(mpBall.get());
}

enum Game::State Game::state() const { return mState; }

} // namespace bd
