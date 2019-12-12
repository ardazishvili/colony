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

void Buildable::select()
{
  _status = Status::Selected;
  _viewPtr->setTexture(Status::Selected);
}

void Buildable::deselect()
{
  if (_status != Status::Destroyed) {
    _status = Status::None;
    _viewPtr->setTexture(Status::None);
  }
}
