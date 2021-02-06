#ifndef TANK_BUILDER_H
#define TANK_BUILDER_H

#include "../fig/Shader.h"

#include "AbstractUnitBuilder.h"
#include "Tank.h"
#include "TankFactory.h"

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
