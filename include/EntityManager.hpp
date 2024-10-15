#pragma once

#include "Ball.hpp"
#include "BlockManager.hpp"
#include "Entity.hpp"

#include <memory>
#include <optional>
#include <variant>

namespace bd {
class Game;

class EntityManager {
public:
  EntityManager(Point&& ballStartPos, Game* pGame);

  void update();

  Ball& ball();

  const BlockManager& blockManager() const;
  BlockManager& blockManager();

  unsigned int score() const;

private:
  struct CollisionEntity {};

  struct WallCollisionEntity : public CollisionEntity {
    WallCollisionEntity(Vector::Axis side) : impactSide(side) {}
    Vector::Axis impactSide;
  };

  struct OutOfBoundsCollisionEntity : public CollisionEntity {};

  struct BlockCollisionEntity : public CollisionEntity {
    BlockCollisionEntity(BlockManager::Indices&& idx, std::vector<Vector::Axis>&& sides)
        : indices(std::move(idx)), impactSides(std::move(sides)) {}
    BlockManager::Indices indices;
    std::vector<Vector::Axis> impactSides;
  };

  using CollisionEntities =
      std::variant<WallCollisionEntity, OutOfBoundsCollisionEntity,
                   BlockCollisionEntity>;

  std::optional<CollisionEntities> check(EntityType entity);

  Ball mBall;
  BlockManager mBlockManager;

  Game* mpGame;
};

} // namespace bd
