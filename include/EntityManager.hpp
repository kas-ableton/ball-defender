#pragma once

#include "Ball.hpp"
#include "BlockManager.hpp"
#include "Entity.hpp"
#include "GameModel.hpp"

#include <memory>
#include <optional>
#include <variant>

namespace bd {

class EntityManager {
public:
  EntityManager(Point&& ballStartPos, GameModel* pModel);

  void update();

  Ball& ball();

  const BlockManager& blockManager() const;
  BlockManager& blockManager();

private:
  struct CollisionEntity {};

  struct WallCollisionEntity : public CollisionEntity {
    WallCollisionEntity(Vector::Axis side) : impactSide(side) {}
    Vector::Axis impactSide;
  };

  struct OutOfBoundsCollisionEntity : public CollisionEntity {};

  struct BlockCollisionEntity : public CollisionEntity {
    BlockCollisionEntity(Block* pBlock, Vector::Axis side)
        : block(pBlock), impactSide(side) {}
    Block* block;
    Vector::Axis impactSide;
  };

  using CollisionEntities =
      std::variant<WallCollisionEntity, OutOfBoundsCollisionEntity,
                   BlockCollisionEntity>;

  std::optional<CollisionEntities>
  check(const EntityManager* const entityManager, EntityType entity);

  Ball mBall;
  BlockManager mBlockManager;

  GameModel* mpGameModel;
};

} // namespace bd
