#pragma once

namespace bd {
class Point;
}

namespace bd {
enum class EntityType {
  Ball,
  BlockManager,
  PowerUp,
};

class Entity {
public:
  Entity(EntityType type);

  virtual Point position() const = 0;

  EntityType type() const;

  virtual void update() = 0;

private:
  EntityType mType;
};

} // namespace bd
