#include "logic/structures/TankFactory.h"

#include "logic/builders/TankBuilder.h"

TankFactory::TankFactory(fig::AStar& router, glm::vec3 position)
    : GroundStructure(std::make_unique<TankFactoryView>(position)),
      _router(router) {
  std::cout << "position.x= " << position.x << std::endl;
  std::cout << "position.y= " << position.y << std::endl;
  _health = TANK_FACTORY_HP;
  _maxHealth = _health;
}

void TankFactory::createTank(Game& game, Tank::Type tankType,
                             HealthLevel healthLevel, Shell::Size shellSize) {
  auto p = position();
  auto d = 3.0f;
  auto tankDestination =
      glm::vec3(p.x - d * ::cos(glm::radians(_view->angle())),
                p.y - d * ::sin(glm::radians(_view->angle())), p.z);
  ::createTank(game, _router, position(), tankDestination, tankType,
               healthLevel, shellSize);
}

UnitBuilders TankFactory::getUnitBuilders() {
  auto builders = UnitBuilders();
  addUnitBuilder(builders, Tank::Type::Light, HealthLevel::High,
                 Shell::Size::Small);
  addUnitBuilder(builders, Tank::Type::Medium, HealthLevel::High,
                 Shell::Size::Medium);
  addUnitBuilder(builders, Tank::Type::Heavy, HealthLevel::High,
                 Shell::Size::Big);
  return builders;
}

void TankFactory::addUnitBuilder(UnitBuilders& builders, Tank::Type type,
                                 HealthLevel healthLevel,
                                 Shell::Size shellSize) {
  builders.push_back(
      std::make_unique<TankBuilder>(*this, type, healthLevel, shellSize));
}

StructureBuilders TankFactory::getStructureBuilders() {
  return StructureBuilders();
}
