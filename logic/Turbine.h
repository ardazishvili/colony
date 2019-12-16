#ifndef TURBINE_H
#define TURBINE_H

#include <glm/glm.hpp>

#include "../view/TurbineView.h"
#include "EnergyStructure.h"

class Turbine : public EnergyStructure
{
public:
  Turbine(Shader& textureShader,
          Shader& linesShader,
          Game* game,
          glm::vec3 position);
  UnitBuilders getUnitBuilders(Game* game) override;
  StructureBuilders getStructureBuilders() override;

private:
  Game* _game;
  static const int TURBINE_HP;
};

#endif
