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

void Game::run() {
}

void Game::start() {
  mState = State::LaunchReady;

  mScore = 0;

  mpPlayArea = std::make_unique<sf::RectangleShape>(
      sf::Vector2f(bd::kPlayAreaX, bd::kPlayAreaY));
  mpPlayArea->setFillColor(sf::Color(100, 250, 50));
  mpPlayArea->setPosition(bd::kWindowPadding, bd::kWindowPadding);

  mDrawObjects.push_back(mpPlayArea.get());
}

enum Game::State Game::state() const { return mState; }

} // namespace bd
