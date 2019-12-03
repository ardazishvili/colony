#include <iostream>

#include "TankBuilder.h"

std::map<Tank::Type, MenuTextures> tankTypeToPreviewMapping = {
  { Tank::Type::Light, MenuTextures::TankLight },
  { Tank::Type::Medium, MenuTextures::TankMedium },
  { Tank::Type::Heavy, MenuTextures::TankHeavy },
};

TankBuilder::TankBuilder(Shader& shader,
			 Game& game, 
			 TankFactory& tankFactory,
			 Tank::Type tankType,
	      		 HealthLevel healthLevel,
	      		 Shell::Size shellSize) :
	_shader(shader),
	_type(tankType),
	_healthLevel(healthLevel),
	_shellSize(shellSize),
	_game(game),
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

MenuTextures TankBuilder::getPreviewType()
{
  return tankTypeToPreviewMapping[_type];
}
