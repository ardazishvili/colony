#ifndef TANK_FACTORY_H
#define TANK_FACTORY_H

#include "../view/TankFactoryView.h"
#include "BuildableStructure.h"
#include "Tank.h"

class Game;

class TankFactory : public BuildableStructure
{
public:
  TankFactory() = delete;
  TankFactory(Shader& textureShader,
              Shader& linesShader,
              AStar* router,
              glm::vec3 position);

  void createTank(Game* game,
                  Tank::Type tankType,
                  HealthLevel healthLevel,
                  Shell::Size shellSize);
  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;

private:
  void addUnitBuilder(Game* game,
                      UnitBuilders& builders,
                      Tank::Type type,
                      HealthLevel healthLevel,
                      Shell::Size shellSize);

  static const int TANK_FACTORY_HP;
  AStar* _router{ nullptr };
};

#endif
