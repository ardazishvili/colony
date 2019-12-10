#include "TankFactory.h"
#include "TankBuilder.h"

const int TankFactory::TANK_FACTORY_HP = 200;

TankFactory::TankFactory(Shader& shader, glm::vec3 position) :
  _view(shader, position), _shader(shader)
{
  _health = TANK_FACTORY_HP;
  _maxHealth = _health;
}

void TankFactory::render()
{
  _view.draw();
}

void TankFactory::createTank(Game& game,
                             Tank::Type tankType,
                             HealthLevel healthLevel,
                             Shell::Size shellSize)
{
  auto x = position().x + 0.0f;
  auto y = position().y + 0.0f;
  auto z = position().z + 0.0f;
  auto tank = ::createTank(
    game, _shader, glm::vec3(x, y, z), tankType, healthLevel, shellSize);
  auto d = 3.0f;
  auto tankDestination = glm::vec3(x - d * ::cos(glm::radians(_view.angle())),
                                   y - d * ::sin(glm::radians(_view.angle())),
                                   z);
  tank->startMoving(tankDestination);
}

bool TankFactory::isUnderCursor(const glm::vec3& mousePoint)
{
  return _view.contain(mousePoint);
}

void TankFactory::select()
{
  _view.setTexture(Status::Selected);
}

void TankFactory::deselect()
{
  if (_status != Status::Destroyed) {
    _status = Status::None;
    _view.setTexture(Status::None);
  }
}

void TankFactory::updateHealthBar()
{
  auto factor = _health / _maxHealth;
  _view.setHealthBarScaleFactor(factor);
}

void TankFactory::takeDamage(Shell::Size shellSize)
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

glm::vec3 TankFactory::position()
{
  return _view.position();
}

UnitBuilders TankFactory::getUnitBuilders(Game& game)
{
  auto builders = UnitBuilders();
  addUnitBuilder(
    game, builders, Tank::Type::Light, HealthLevel::High, Shell::Size::Small);
  addUnitBuilder(
    game, builders, Tank::Type::Medium, HealthLevel::High, Shell::Size::Medium);
  addUnitBuilder(
    game, builders, Tank::Type::Heavy, HealthLevel::High, Shell::Size::Big);
  return builders;
}

void TankFactory::addUnitBuilder(Game& game,
                                 UnitBuilders& builders,
                                 Tank::Type type,
                                 HealthLevel healthLevel,
                                 Shell::Size shellSize)
{
  std::unique_ptr<AbstractUnitBuilder> builder = std::make_unique<TankBuilder>(
    _shader, game, *this, type, healthLevel, shellSize);
  builders.push_back(std::move(builder));
}

StructureBuilders TankFactory::getStructureBuilders()
{
  return StructureBuilders();
}

void TankFactory::setAngle(float angle)
{
  _view.rotate(angle);
}

void TankFactory::setPosition(glm::vec3 position)
{
  _view.move(position);
}

void TankFactory::commit()
{
  deselect();
}

