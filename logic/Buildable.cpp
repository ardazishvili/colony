#include "Buildable.h"

Buildable::Buildable(Shader& shader) : _shader(shader)
{
}

bool Buildable::isDestroyed() const
{
  return _status == Status::Destroyed;
}

bool Buildable::isUnderFire() const
{
  return _status == Status::UnderFire;
}
