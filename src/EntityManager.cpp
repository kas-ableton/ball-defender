#include "EntityManager.hpp"

#include "Constants.hpp"

namespace bd {

auto EntityManager::check(const EntityManager* const entityManager,
                          EntityType entity) -> std::optional<CollisionEntity> {
  if (entity == EntityType::Ball) {
    const auto ballPos = entityManager->mBall.position();

    if (ballPos.y() == kPlayAreaY) {
      return CollisionEntity{CollisionEntity::Type::outOfBounds,
                             Vector::Axis::Y};
    } else if (ballPos.x() == kPlayAreaX || ballPos.x() == 0) {
      return CollisionEntity{CollisionEntity::Type::wall, Vector::Axis::X};
    } else if (ballPos.y() == 0) {
      return CollisionEntity{CollisionEntity::Type::wall, Vector::Axis::Y};
    }
  }

  return {};
}

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

    if (auto other = check(this, EntityType::Ball)) {
      if (other->type == CollisionEntity::Type::outOfBounds) {
        mpGameModel->setState(GameModel::State::BallDead);
      } else if (other->type == CollisionEntity::Type::wall) {
        mBall.vector().reflect(other->impactSide == Vector::Axis::X
                                   ? Vector::Axis::Y
                                   : Vector::Axis::X);
      }
    }

    break;
  case GameModel::State::BallDead:
    break;
  case GameModel::State::GameOver:
    break;
  }
}

Ball& EntityManager::ball() { return mBall; }

} // namespace bd
