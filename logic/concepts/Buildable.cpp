#include "Buildable.h"

Buildable::Buildable(SelectableView* view) : _view(view)
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

void Buildable::updateHealthBar()
{
  auto factor = _health / _maxHealth;
  _view->setHealthBarScaleFactor(factor);
}

void Buildable::takeDamage(Shell::Size shellSize)
{
  if (_status != Status::Destroyed) {
    _status = Status::UnderFire;
    _view->setTexture(Status::UnderFire);
    _health = std::max(0.0f, _health - Shell::SHELL_DAMAGE_MAP.find(shellSize)->second);
    if (_health == 0) {
      _status = Status::Destroyed;
      _view->setTexture(Status::Destroyed);
    }
    updateHealthBar();
  }
}

glm::vec3 Buildable::position() const
{
  return _view->position();
}
