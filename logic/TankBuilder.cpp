#include "TankBuilder.h"

std::map<Tank::Type, fig::MenuTextures> tankTypeToPreviewMapping = {
  { Tank::Type::Light, fig::MenuTextures::TankLight },
  { Tank::Type::Medium, fig::MenuTextures::TankMedium },
  { Tank::Type::Heavy, fig::MenuTextures::TankHeavy },
};

TankBuilder::TankBuilder(fig::Shader& shader,
                         Game* game,
                         TankFactory& tankFactory,
                         Tank::Type tankType,
                         HealthLevel healthLevel,
                         Shell::Size shellSize) :
  AbstractUnitBuilder(game),
  _shader(shader), _type(tankType), _healthLevel(healthLevel), _shellSize(shellSize), _game(game),
  _tankFactory(tankFactory)
{
}

TankBuilder::~TankBuilder()
{
}

void TankBuilder::create()
{
  _tankFactory.createTank(_game, _type, _healthLevel, _shellSize);
}

fig::MenuTextures TankBuilder::getPreviewType()
{
  return tankTypeToPreviewMapping[_type];
}
