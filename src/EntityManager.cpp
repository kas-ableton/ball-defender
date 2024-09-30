#include "EntityManager.hpp"

#include "Constants.hpp"

#include <variant>

namespace bd {

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

EntityManager::EntityManager(Point&& ballStartPos, GameModel* pModel)
    : mBall(std::move(ballStartPos)),
      mBlockManager(kPlayAreaY - kBlockSizeY, kBlockSizeY),
      mpGameModel(pModel) {}

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
    } else if (auto block = mBlockManager.blockAtPosition(ballPos)) {
      if (auto impactSide = block->impactSide(ballPos)) {
        return BlockCollisionEntity{&*block, impactSide == Vector::Axis::X
                                                 ? Vector::Axis::Y
                                                 : Vector::Axis::X};
      }
    }
  }

  return {};
}

void EntityManager::update() {
  switch (mpGameModel->state()) {
  case GameModel::State::Unstarted:
    break;
  case GameModel::State::LaunchReady:
    break;
  case GameModel::State::BallInMotion:
    mBall.update();

    if (auto other = check(this, EntityType::Ball)) {
      std::visit(overloaded{[this](const OutOfBoundsCollisionEntity&) {
                              mpGameModel->setState(GameModel::State::BallDead);
                            },
                            [this](const WallCollisionEntity& wall) {
                              mBall.vector().reflect(wall.impactSide ==
                                                             Vector::Axis::X
                                                         ? Vector::Axis::Y
                                                         : Vector::Axis::X);
                            },
                            [this](BlockCollisionEntity& block) {
                              mBall.vector().reflect(block.impactSide ==
                                                             Vector::Axis::X
                                                         ? Vector::Axis::Y
                                                         : Vector::Axis::X);
                              block.block--;
                            }},
                 *other);
    }

    break;
  case GameModel::State::BallDead:
    if (mBlockManager.atBlockRowMax()) {
      mpGameModel->setState(GameModel::State::GameOver);
    } else {
      mBlockManager.advanceBlockRows();
      mBlockManager.addBlockRow();
      mBall.reset();
      mpGameModel->setState(GameModel::State::LaunchReady);
    }
    break;
  case GameModel::State::GameOver:
    break;
  }
}

Ball& EntityManager::ball() { return mBall; }

const BlockManager& EntityManager::blockManager() const { return mBlockManager; }

BlockManager& EntityManager::blockManager() { return mBlockManager; }

} // namespace bd
