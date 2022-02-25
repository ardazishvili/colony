#pragma once

#include "logic/builders/AbstractUnitBuilder.h"
#include "logic/structures/TankFactory.h"
#include "logic/units/Tank.h"

class TankBuilder : public AbstractUnitBuilder {
 public:
  TankBuilder(TankFactory& _tankFactory, Tank::Type tankType,
              HealthLevel healthLevel, Shell::Size shellSize);
  ~TankBuilder();

  void addToGame(Game& game) override;
  fig::MenuTextures getPreviewType() override;

 private:
  Tank::Type _type;
  HealthLevel _healthLevel;
  Shell::Size _shellSize;
  TankFactory& _tankFactory;
};
