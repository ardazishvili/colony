#ifndef TANK_BUILDER_H
#define TANK_BUILDER_H

#include "../engine/Shader.h"
#include "AbstractUnitBuilder.h"
#include "Tank.h"
#include "TankFactory.h"

class TankBuilder : public AbstractUnitBuilder
{
public:
  TankBuilder(Shader& shader,
              Game* game,
              TankFactory& _tankFactory,
              Tank::Type tankType,
              HealthLevel healthLevel,
              Shell::Size shellSize);
  ~TankBuilder();

  void create() override;
  MenuTextures getPreviewType() override;

private:
  Shader& _shader;
  Tank::Type _type;
  HealthLevel _healthLevel;
  Shell::Size _shellSize;
  Game* _game;
  TankFactory& _tankFactory;
};

#endif
