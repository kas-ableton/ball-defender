#include "EntityManager.hpp"

#include "Constants.hpp"
#include "Game.hpp"

#include <variant>

namespace bd {

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

EntityManager::EntityManager(Point&& ballStartPos, Game* pGame)
    : mBall(std::move(ballStartPos)),
      mBlockManager(kBlockSizeY, kPlayAreaY - bd::kBlockSizeY, bd::kPlayAreaX),
      mpGame(pGame) {}

auto EntityManager::check(EntityType entity)
    -> std::optional<CollisionEntities> {
  if (entity == EntityType::Ball) {
    const auto ballPos = mBall.position();

    if (ballPos.y() == kPlayAreaY) {
      return OutOfBoundsCollisionEntity{};
    } else if (ballPos.x() == kPlayAreaX || ballPos.x() == kWindowPadding) {
      return WallCollisionEntity{Vector::Axis::X};
    } else if (ballPos.y() == kWindowPadding) {
      return WallCollisionEntity{Vector::Axis::Y};

    } else if (auto blockCollisions = mBlockManager.blockCollisions(
                   mBall.position() - bd::kWindowPadding)) {
      return BlockCollisionEntity{
          std::move(blockCollisions->front().blockIndices),
          std::move(blockCollisions->front().sides)};
    }
  }

  return {};
}

void EntityManager::update() {
  switch (mpGame->state()) {
    // nothing to do, wait for user input
  case Game::State::Unstarted:
  case Game::State::LaunchReady:
    break;
  case Game::State::StartNewRound:
    mBlockManager.addNewRow();
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
                              mBall.reflect(wall.impactSide == Vector::Axis::X
                                                ? Vector::Axis::Y
                                                : Vector::Axis::X);
                            },
                            [this](BlockCollisionEntity& block) {
                              for (const auto side : block.impactSides) {
                                mBall.reflect(side == Vector::Axis::X
                                                  ? Vector::Axis::Y
                                                  : Vector::Axis::X);
                              }
                              mBlockManager.decrementBlockHitCount(
                                  block.indices);
                            }},
                 *other);
    }

    break;
  case Game::State::BallDead:
    if (mBlockManager.atMaxRowHeight()) {
      mpGame->setState(Game::State::GameOver);
    } else {
      mpGame->setState(Game::State::StartNewRound);
    }
    break;
  case Game::State::GameOver:
    mBlockManager.reset();
    mBall.reset();
    break;
  }
}

Ball& EntityManager::ball() { return mBall; }

const BlockManager& EntityManager::blockManager() const {
  return mBlockManager;
}

BlockManager& EntityManager::blockManager() { return mBlockManager; }

unsigned int EntityManager::score() const {
  return mBlockManager.runningRowCount();
}
} // namespace bd
