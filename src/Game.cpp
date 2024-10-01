#include "Game.hpp"
#include "Constants.hpp"
#include "Point.hpp"

#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

namespace bd {

Game::Game(sf::RenderWindow* window)
    : mGameView(window, this, &mEntityManager),
      mEntityManager({bd::kBallStartPosX, bd::kBallStartPosY}, this) {}

void Game::setState(State newState) { mState = newState; }

auto Game::state() const -> State { return mState; }

void Game::handleEvent(const sf::Event& event) {
  if (state() == State::Unstarted) {
    if (event.type == sf::Event::MouseButtonReleased) {
      start();
    }
  } else if (state() == State::LaunchReady) {
    if (event.type == sf::Event::MouseButtonPressed) {
      mLaunchStart = {event.mouseButton.x, event.mouseButton.y};
    } else if (event.type == sf::Event::MouseButtonReleased) {
      // assert(mLaunchStart, "mLaunchStart invalid");
      mEntityManager.ball().onLaunch(
          std::move(mLaunchStart), {event.mouseButton.x, event.mouseButton.y});
      setState(State::BallInMotion);
    }
  } else if (state() == State::GameOver) {
  }
}

void Game::run() {
  mEntityManager.update();
  mGameView.draw();
}

void Game::start() {
  setState(State::LaunchReady);

  mEntityManager.blockManager().addBlockRow();
}

} // namespace bd
