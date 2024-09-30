#include "Entity.hpp"

namespace bd {
Entity::Entity(EntityType type) : mType(type) {}

EntityType Entity::type() const { return mType; }
} // namespace bd
