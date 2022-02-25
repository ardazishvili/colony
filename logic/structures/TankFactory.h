#pragma once

#include "logic/Game.h"
#include "logic/structures/GroundStructure.h"
#include "logic/units/Tank.h"
#include "view/TankFactoryView.h"

class Game;

class TankFactory : public GroundStructure {
 public:
  TankFactory() = delete;
  TankFactory(fig::AStar& router, glm::vec3 position);

  void createTank(Game& game, Tank::Type tankType, HealthLevel healthLevel,
                  Shell::Size shellSize);
  UnitBuilders getUnitBuilders() override;
  StructureBuilders getStructureBuilders() override;

 private:
  void addUnitBuilder(UnitBuilders& builders, Tank::Type type,
                      HealthLevel healthLevel, Shell::Size shellSize);

  static const int TANK_FACTORY_HP;
  fig::AStar& _router;
};
