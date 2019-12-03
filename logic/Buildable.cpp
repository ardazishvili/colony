#include "Buildable.h"

bool Buildable::isDestroyed() const
{
  return _status == Status::Destroyed;
}

bool Buildable::isUnderFire() const
{
  return _status == Status::UnderFire;
}
