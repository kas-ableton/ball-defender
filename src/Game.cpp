#include "Game.hpp"

#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

namespace bd {

Game::Game(sf::RenderWindow* window) : mGameView(window) {}

void Game::handleEvent(const sf::Event& event) {
  if (mGameModel.state() == bd::GameModel::State::Unstarted) {
    if (event.type == sf::Event::MouseButtonReleased) {
      start();
    }
  } else if (mGameModel.state() == bd::GameModel::State::LaunchReady) {
    if (event.type == sf::Event::MouseButtonReleased) {
    }
  }
}

void Game::run() { mGameView.draw(); }

void Game::start() {
  mGameModel.setState(GameModel::State::LaunchReady);

  mGameModel.resetScore();

  mGameView.handleState();
}

} // namespace bd
