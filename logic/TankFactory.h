#ifndef TANK_FACTORY_H
#define TANK_FACTORY_H

#include "GroundStructure.h"
#include "Tank.h"

#include "../view/TankFactoryView.h"

class Game;

class TankFactory : public GroundStructure
{
public:
  TankFactory() = delete;
  TankFactory(fig::Shader& textureShader, fig::Shader& linesShader, fig::AStar* router, glm::vec3 position);

  void createTank(Game* game, Tank::Type tankType, HealthLevel healthLevel, Shell::Size shellSize);
  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;

private:
  void addUnitBuilder(Game* game,
                      UnitBuilders& builders,
                      Tank::Type type,
                      HealthLevel healthLevel,
                      Shell::Size shellSize);

  static const int TANK_FACTORY_HP;
  fig::AStar* _router{ nullptr };
};

#endif
