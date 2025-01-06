#include "EntityManager.hpp"

#include "Constants.hpp"
#include "CollisionConstants.hpp"
#include "Game.hpp"
#include "LaunchRay.hpp"

#include <variant>

namespace bd {

constexpr int kMaxBallPositionX = bd::kPlayAreaX - bd::kBallRadius;

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

EntityManager::EntityManager(Point&& ballStartPos, Game* pGame)
    : mBall(std::move(ballStartPos), static_cast<float>(kMaxBallPositionX),
            static_cast<float>(bd::kPlayAreaY)),
      mBlockManager(kBlockSizeY, kPlayAreaY - bd::kBlockSizeY, bd::kPlayAreaX),
      mpGame(pGame) {}

auto EntityManager::check(EntityType entity)
    -> std::optional<CollisionEntities> {
  if (entity == EntityType::Ball) {
    const auto ballPos = mBall.position();

    if (ballPos.y() == kPlayAreaY) {
      return OutOfBoundsCollisionEntity{};
    } else if (ballPos.x() == kMaxBallPositionX) {
      return WallCollisionEntity{kRightSideNormal};
    } else if (ballPos.x() == 0.0) {
      return WallCollisionEntity{kLeftSideNormal};
    } else if (ballPos.y() == 0.0) {
      return WallCollisionEntity{kBottomSideNormal};
    } else if (auto blockCollisions =
                   mBlockManager.blockCollisions(mBall, bd::kBallRadius * 2)) {
      return BlockCollisionEntity{
          std::move(blockCollisions->front().blockIndices),
          std::move(blockCollisions->front().normal)};
    }
  }

  return {};
}

void EntityManager::update(float deltaTimeSec) {
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
    mBall.update(deltaTimeSec);

    if (auto other = check(EntityType::Ball)) {
      std::visit(
          overloaded{
              [this](const OutOfBoundsCollisionEntity&) {
                mpGame->setState(Game::State::BallDead);
              },
              [this](const WallCollisionEntity& wall) {
                mBall.setVector(Vector::reflect(mBall.vector(), wall.normal));
              },
              [this](BlockCollisionEntity& block) {
                mBall.setVector(Vector::reflect(mBall.vector(), block.normal));
                mBlockManager.decrementBlockHitCount(block.indices);
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

std::optional<LaunchRay> EntityManager::launchRay() { return mLaunchRay; }

void EntityManager::startLaunchRay(const Point& launchStart) {
  mLaunchRay = std::make_optional(getLaunchRayStartPosition(mBall.position()));
  mLaunchRay->onDragStart(launchStart);
  mLaunchRay->onDragUpdate(launchStart);
}

void EntityManager::onDragUpdate(const Point& launchEnd) {
  mLaunchRay->onDragUpdate(launchEnd);
}

void EntityManager::clearLaunchRay() { mLaunchRay = std::nullopt; }

unsigned int EntityManager::score() const {
  return mBlockManager.runningRowCount();
}

Point EntityManager::getLaunchRayStartPosition(
    const Point& ballPosition) const {
  static const int kLaunchRayStartPosY = kBallStartPosY + kBallRadius;
  return Point{mBall.position().x() + static_cast<int>(bd::kBallRadius) +
                   static_cast<int>(kLaunchRayWidth / 2),
               kLaunchRayStartPosY};
}
} // namespace bd
