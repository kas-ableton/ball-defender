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
    WallCollisionEntity(const Vector& n) : normal(n) {}
    Vector normal;
  };

  struct OutOfBoundsCollisionEntity : public CollisionEntity {};

  struct BlockCollisionEntity : public CollisionEntity {
    BlockCollisionEntity(BlockManager::Indices&& idx, Vector&& collisionNormal)
        : indices(std::move(idx)), normal(std::move(collisionNormal)) {}
    BlockManager::Indices indices;
    Vector normal;
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
