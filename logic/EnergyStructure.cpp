#include "EnergyStructure.h"

EnergyStructure::EnergyStructure(Shader& textureShader,
                                 Shader& linesShader,
                                 std::unique_ptr<StructureView> view) :
  GroundStructure(textureShader, linesShader, std::move(view))
{
}
