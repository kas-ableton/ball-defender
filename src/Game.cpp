#include "Constants.hpp"
#include "Game.hpp"
#include "Point.hpp"

#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

namespace bd {

Game::Game(sf::RenderWindow* window)
    : mGameModel({bd::kBallStartPosX, bd::kBallStartPosY}),
      mGameView(window, &mGameModel) {}

void Game::handleEvent(const sf::Event& event) {
  if (mGameModel.state() == bd::GameModel::State::Unstarted) {
    if (event.type == sf::Event::MouseButtonReleased) {
      start();
    }
  } else if (mGameModel.state() == bd::GameModel::State::LaunchReady) {
    if (event.type == sf::Event::MouseButtonPressed) {
      mGameModel.onLaunchStart({event.mouseButton.x, event.mouseButton.y});
    } else if (event.type == sf::Event::MouseButtonReleased) {
      mGameModel.onLaunchEnd({event.mouseButton.x, event.mouseButton.y});
      mGameModel.setState(GameModel::State::BallInMotion);
    }
  } else if (mGameModel.state() == bd::GameModel::State::BallInMotion) {
  } else if (mGameModel.state() == bd::GameModel::State::BallDead) {
  }
}

void Game::run() { mGameView.draw(); }

void Game::start() {
  mGameModel.setState(GameModel::State::LaunchReady);

  mGameModel.resetScore();

  mGameView.handleState();
}

} // namespace bd
