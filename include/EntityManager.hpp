#pragma once

#include "Ball.hpp"
#include "Entity.hpp"
#include "GameModel.hpp"

#include <memory>

namespace bd {
class EntityManager {
public:
  EntityManager(Point&& ballStartPos, GameModel* pModel);

  void update();

  Ball& ball();
  Point ballPosition() const;

private:
  Ball mBall;

  GameModel* mpGameModel;
};

} // namespace bd
