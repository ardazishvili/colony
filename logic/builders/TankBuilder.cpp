#include "logic/builders/TankBuilder.h"

std::map<Tank::Type, fig::MenuTextures> tankTypeToPreviewMapping = {
    {Tank::Type::Light, fig::MenuTextures::TankLight},
    {Tank::Type::Medium, fig::MenuTextures::TankMedium},
    {Tank::Type::Heavy, fig::MenuTextures::TankHeavy},
};

TankBuilder::TankBuilder(TankFactory& tankFactory, Tank::Type tankType,
                         HealthLevel healthLevel, Shell::Size shellSize)
    : AbstractUnitBuilder(),
      _type(tankType),
      _healthLevel(healthLevel),
      _shellSize(shellSize),
      _tankFactory(tankFactory) {}

TankBuilder::~TankBuilder() {}

void TankBuilder::addToGame(Game& game) {
  _tankFactory.createTank(game, _type, _healthLevel, _shellSize);
}

fig::MenuTextures TankBuilder::getPreviewType() {
  return tankTypeToPreviewMapping[_type];
}
