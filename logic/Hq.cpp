#include "Hq.h"
#include "BarrierBuilder.h"
#include "TankFactoryBuilder.h"

const int Hq::HQ_HP = 500;

Hq::Hq(Shader& shader, glm::vec3 position, Terrain* terrain) :
  _shader(shader), _view(shader, position), _terrain(terrain)
{
  _health = HQ_HP;
  _maxHealth = _health;
}

void Hq::render()
{
  _view.draw();
}

bool Hq::isUnderCursor(const glm::vec3& mousePoint)
{
  return _view.contain(mousePoint);
}

void Hq::select()
{
  _view.setTexture(Status::Selected);
}

void Hq::deselect()
{
  if (_status != Status::Destroyed) {
    _status = Status::None;
    _view.setTexture(Status::None);
  }
}

void Hq::updateHealthBar()
{
  auto factor = _health / _maxHealth;
  _view.setHealthBarScaleFactor(factor);
}

void Hq::takeDamage(Shell::Size shellSize)
{
  if (_status != Status::Destroyed) {
    _status = Status::UnderFire;
    _view.setTexture(Status::UnderFire);
    _health =
      std::max(0.0f, _health - Shell::SHELL_DAMAGE_MAP.find(shellSize)->second);
    if (_health == 0) {
      _status = Status::Destroyed;
      _view.setTexture(Status::Destroyed);
    }
    updateHealthBar();
  }
}

glm::vec3 Hq::position()
{
  return _view.position();
}

UnitBuilders Hq::getUnitBuilders(Game& game)
{
  return UnitBuilders();
}

StructureBuilders Hq::getStructureBuilders()
{
  StructureBuilders builders = StructureBuilders();
  std::unique_ptr<AbstractStructureBuilder> tfBuilder =
    std::make_unique<TankFactoryBuilder>(_shader);
  builders.push_back(std::move(tfBuilder));

  std::unique_ptr<AbstractStructureBuilder> bBuilder =
    std::make_unique<BarrierBuilder>(_shader, _terrain);
  builders.push_back(std::move(bBuilder));

  return builders;
}

void Hq::setAngle(float angle)
{
  _view.rotate(angle);
}

void Hq::setPosition(glm::vec3 position)
{
  _view.move(position);
}

void Hq::commit()
{
  deselect();
}

