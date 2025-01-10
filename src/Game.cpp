#include "Game.hpp"
#include "Constants.hpp"
#include "Point.hpp"

#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

#include <filesystem>

namespace bd {

Game::Game(sf::RenderWindow* window, const std::filesystem::path& resourcesPath)
    : mGameView(window, this, &mEntityManager, resourcesPath),
      mEntityManager({bd::kBallStartPosX, bd::kBallStartPosY}, this) {}

void Game::setState(State newState) { mState = newState; }

auto Game::state() const -> State { return mState; }

void Game::handleEvent(const sf::Event& event) {
  if (state() == State::Unstarted) {
    if (event.type == sf::Event::MouseButtonReleased) {
      setState(State::StartNewRound);
    }
  } else if (state() == State::LaunchReady) {
    if (event.type == sf::Event::MouseButtonPressed) {
      mLaunchStart =
          std::make_optional<Point>(event.mouseButton.x, event.mouseButton.y);
      mEntityManager.startLaunchRay(*mLaunchStart);
    } else if (event.type == sf::Event::MouseMoved &&
               mLaunchStart != std::nullopt) {

      mLaunchEnd = {event.mouseMove.x, event.mouseMove.y};

      mEntityManager.onDragUpdate(mLaunchEnd);

      auto lr = *mEntityManager.launchRay();
    } else if (event.type == sf::Event::MouseButtonReleased) {
      // assert(mLaunchStart, "mLaunchStart invalid");

      // handle invalid ball trajectory
      if (mLaunchStart->x() == event.mouseButton.x &&
          mLaunchStart->y() == event.mouseButton.y) {
        mLaunchStart = std::nullopt;
        setState(State::BallDead);
        return;
      }

      mEntityManager.clearLaunchRay();
      mEntityManager.ball().onLaunch(
          std::move(*mLaunchStart), {event.mouseButton.x, event.mouseButton.y});
      mLaunchStart = std::nullopt;

      // don't play a ball that only moves horizontally
      if (mEntityManager.ball().vector().y == 0.f) {
        setState(State::BallDead);
        return;
      }

      setState(State::BallInMotion);
    }
  } else if (state() == State::GameOver) {
    if (event.type == sf::Event::MouseButtonReleased) {
      setState(State::Unstarted);
    }
  }
}

void Game::run(float deltaTimeSec) {
  mEntityManager.update(deltaTimeSec);
  mGameView.draw(deltaTimeSec);
}

unsigned int Game::score() const { return mEntityManager.score(); }

} // namespace bd
