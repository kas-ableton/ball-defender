#include "EntityManager.hpp"

#include "Constants.hpp"
#include "Game.hpp"

#include <variant>

namespace bd {

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...)->overloaded<Ts...>;

EntityManager::EntityManager(Point&& ballStartPos, Game* pGame)
    : mBall(std::move(ballStartPos)),
      mBlockManager(kPlayAreaY - kBlockSizeY, kBlockSizeY), mpGame(pGame) {}

auto EntityManager::check(EntityType entity)
    -> std::optional<CollisionEntities> {
  if (entity == EntityType::Ball) {
    const auto ballPos = mBall.position();

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
  switch (mpGame->state()) {
  case Game::State::Unstarted:
    break;
  case Game::State::LaunchReady:
    break;
  case Game::State::StartNewRound:
    mBlockManager.advanceBlockRows();
    mBlockManager.addBlockRow();
    mBall.reset();
    mpGame->setState(Game::State::LaunchReady);
    break;
  case Game::State::BallInMotion:
    mBall.update();

    if (auto other = check(EntityType::Ball)) {
      std::visit(overloaded{[this](const OutOfBoundsCollisionEntity&) {
                              mpGame->setState(Game::State::BallDead);
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
  case Game::State::BallDead:
    if (mBlockManager.atBlockRowMax()) {
      mpGame->setState(Game::State::GameOver);
    } else {
      mpGame->setState(Game::State::StartNewRound);
    }
    break;
  case Game::State::GameOver:
    break;
  }
}

Ball& EntityManager::ball() { return mBall; }

const BlockManager& EntityManager::blockManager() const {
  return mBlockManager;
}

BlockManager& EntityManager::blockManager() { return mBlockManager; }

unsigned int EntityManager::score() const { return mBlockManager.rowDepth(); }
} // namespace bd
