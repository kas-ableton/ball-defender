#include "EntityManager.hpp"

#include "Constants.hpp"

#include <variant>

namespace bd {

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

auto EntityManager::check(const EntityManager* const entityManager,
                          EntityType entity)
    -> std::optional<CollisionEntities> {
  if (entity == EntityType::Ball) {
    const auto ballPos = entityManager->mBall.position();

    if (ballPos.y() == kPlayAreaY) {
      return OutOfBoundsCollisionEntity{};
    } else if (ballPos.x() == kPlayAreaX || ballPos.x() == 0) {
      return WallCollisionEntity{Vector::Axis::X};
    } else if (ballPos.y() == 0) {
      return WallCollisionEntity{Vector::Axis::Y};
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
      std::visit(overloaded{
                     [this](const OutOfBoundsCollisionEntity&) {
                       mpGameModel->setState(GameModel::State::BallDead);
                     },
                     [this](const WallCollisionEntity& wall) {
                       mBall.vector().reflect(wall.impactSide == Vector::Axis::X
                                                  ? Vector::Axis::Y
                                                  : Vector::Axis::X);
                     },
                 },
                 *other);
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
