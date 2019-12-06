#include "Hq.h"
#include "TankFactoryBuilder.h"

const int Hq::HQ_HP = 500;

Hq::Hq(Shader& shader, glm::vec2 position) :
  _shader(shader), _view(shader, position)
{
  _health = HQ_HP;
  _maxHealth = _health;
}

void Hq::display()
{
  _view.draw();
}

bool Hq::isUnderCursor(const glm::vec2& mousePoint)
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

glm::vec2 Hq::position()
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
  std::unique_ptr<AbstractStructureBuilder> builder =
    std::make_unique<TankFactoryBuilder>(_shader);
  builders.push_back(std::move(builder));
  return builders;
}

void Hq::setAngle(float angle)
{
  _view.rotate(angle);
}

void Hq::setPosition(glm::vec2 position)
{
  _view.move(position);
}

void Hq::commit()
{
  deselect();
}

