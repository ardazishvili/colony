#ifndef TURBINE_H
#define TURBINE_H

#include "EnergyStructure.h"

#include "../view/TurbineView.h"

class Turbine : public EnergyStructure
{
public:
  Turbine(fig::Shader& textureShader, fig::Shader& linesShader, Game* game, glm::vec3 position);
  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;
  void commit() override;

private:
  Game* _game;
  static const int TURBINE_HP;
};

#endif
