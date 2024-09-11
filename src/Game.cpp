#include "Game.hpp"
#include "Constants.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace bd {

Game::Game(sf::RenderWindow* window) : mGameView(window) {}

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
  mGameView.draw();
}

void Game::start() {
  mState = State::LaunchReady;

  mScore = 0;


  mGameView.setup();
}

enum Game::State Game::state() const { return mState; }

} // namespace bd
