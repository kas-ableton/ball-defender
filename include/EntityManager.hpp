#pragma once

#include "Ball.hpp"
#include "Entity.hpp"
#include "GameModel.hpp"

#include <memory>
#include <optional>

namespace bd {

class EntityManager {
public:
  EntityManager(Point&& ballStartPos, GameModel* pModel);

  void update();

  Ball& ball();
  Point ballPosition() const;

private:
  struct CollisionEntity {
    enum class Type {
      wall,
      block,
      outOfBounds,
    };

    Type type;
    Vector::Axis impactSide;
  };

  std::optional<CollisionEntity> check(const EntityManager* const entityManager,
                                       EntityType entity);

  Ball mBall;

  GameModel* mpGameModel;
};

} // namespace bd
