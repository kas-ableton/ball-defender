#include "EntityManager.hpp"

#include "Constants.hpp"

namespace bd {

EntityManager::EntityManager(Point&& ballStartPos, GameModel* pModel)
    : mBall(std::move(ballStartPos)), mpGameModel(pModel) {}

void EntityManager::update() {
  switch (mpGameModel->state()) {
  case GameModel::State::Unstarted:
    break;
  case GameModel::State::LaunchReady:
    mBall.resetLaunchPosition();
    break;
  case GameModel::State::BallInMotion:
    mBall.update();

    // TODO move this logic to collision detector
    if (mBall.position().y() == kPlayAreaY) {
      mpGameModel->setState(GameModel::State::BallDead);
    }

    break;
  case GameModel::State::BallDead:
    break;
  }
}

Ball& EntityManager::ball() { return mBall; }

} // namespace bd
