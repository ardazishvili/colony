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

void Buildable::updateHealthBar()
{
  auto factor = _health / _maxHealth;
  _viewPtr->setHealthBarScaleFactor(factor);
}

void Buildable::takeDamage(Shell::Size shellSize)
{
  if (_status != Status::Destroyed) {
    _status = Status::UnderFire;
    _viewPtr->setTexture(Status::UnderFire);
    _health =
      std::max(0.0f, _health - Shell::SHELL_DAMAGE_MAP.find(shellSize)->second);
    if (_health == 0) {
      _status = Status::Destroyed;
      _viewPtr->setTexture(Status::Destroyed);
    }
    updateHealthBar();
  }
}

glm::vec3 Buildable::position() const
{
  return _viewPtr->position();
}

void Buildable::render()
{
  _viewPtr->draw();
}
