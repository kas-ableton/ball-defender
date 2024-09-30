#pragma once

#include "Ball.hpp"
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

  const BlockManager& blockManager();

private:
  struct CollisionEntity {
  };

  struct WallCollisionEntity : public CollisionEntity {
    WallCollisionEntity(Vector::Axis side)
        : impactSide(side) {}
    Vector::Axis impactSide;
  };

  struct OutOfBoundsCollisionEntity : public CollisionEntity {};

  using CollisionEntities =
      std::variant<WallCollisionEntity, OutOfBoundsCollisionEntity>;

  std::optional<CollisionEntities> check(const EntityManager* const entityManager,
                                       EntityType entity);

  Ball mBall;

  GameModel* mpGameModel;
};

} // namespace bd
