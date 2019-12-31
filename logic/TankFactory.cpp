#include "TankFactory.h"
#include "TankBuilder.h"

const int TankFactory::TANK_FACTORY_HP = 200;

TankFactory::TankFactory(Shader& textureShader,
                         Shader& linesShader,
                         AStar* router,
                         glm::vec3 position) :
  BuildableStructure(
    textureShader,
    linesShader,
    std::make_unique<TankFactoryView>(textureShader, position)),
  _router(router)
{
  std::cout << "position.x= " << position.x << std::endl;
  std::cout << "position.y= " << position.y << std::endl;
  _health = TANK_FACTORY_HP;
  _maxHealth = _health;
}

void TankFactory::createTank(Game* game,
                             Tank::Type tankType,
                             HealthLevel healthLevel,
                             Shell::Size shellSize)
{
  auto p = position();
  auto tank = ::createTank(game,
                           _textureShader,
                           _linesShader,
                           _router,
                           position(),
                           tankType,
                           healthLevel,
                           shellSize);
  auto d = 3.0f;
  auto tankDestination =
    glm::vec3(p.x - d * ::cos(glm::radians(_view->angle())),
              p.y - d * ::sin(glm::radians(_view->angle())),
              p.z);
  tank->setRoute(tankDestination);
}

UnitBuilders TankFactory::getUnitBuilders(Game* game)
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

void TankFactory::addUnitBuilder(Game* game,
                                 UnitBuilders& builders,
                                 Tank::Type type,
                                 HealthLevel healthLevel,
                                 Shell::Size shellSize)
{
  std::unique_ptr<AbstractUnitBuilder> builder = std::make_unique<TankBuilder>(
    _textureShader, game, *this, type, healthLevel, shellSize);
  builders.push_back(std::move(builder));
}

StructureBuilders TankFactory::getStructureBuilders()
{
  return StructureBuilders();
}

