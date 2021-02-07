#ifndef TANK_BUILDER_H
#define TANK_BUILDER_H

#include "../../fig/shader/Shader.h"

#include "../structures/TankFactory.h"
#include "../units/Tank.h"
#include "AbstractUnitBuilder.h"

class TankBuilder : public AbstractUnitBuilder
{
public:
  TankBuilder(fig::Shader& shader,
              Game* game,
              TankFactory& _tankFactory,
              Tank::Type tankType,
              HealthLevel healthLevel,
              Shell::Size shellSize);
  ~TankBuilder();

  void create() override;
  fig::MenuTextures getPreviewType() override;

private:
  fig::Shader& _shader;
  Tank::Type _type;
  HealthLevel _healthLevel;
  Shell::Size _shellSize;
  Game* _game;
  TankFactory& _tankFactory;
};

#endif
