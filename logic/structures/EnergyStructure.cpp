#include "EnergyStructure.h"

EnergyStructure::EnergyStructure(fig::Shader& textureShader,
                                 fig::Shader& linesShader,
                                 std::unique_ptr<StructureView> view) :
  GroundStructure(textureShader, linesShader, std::move(view))
{
}
