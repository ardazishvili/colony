#include <memory>

#include "Turbine.h"

const int Turbine::TURBINE_HP = 200;

Turbine::Turbine(Shader& textureShader,
                 Shader& linesShader,
                 glm::vec3 position) :
  EnergyStructure(
    textureShader,
    linesShader,
    std::make_unique<TurbineView>(textureShader, linesShader, position))
{
}

UnitBuilders Turbine::getUnitBuilders(Game* game)
{
  return UnitBuilders();
}

StructureBuilders Turbine::getStructureBuilders()
{
  return StructureBuilders();
}
