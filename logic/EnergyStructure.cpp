#include "EnergyStructure.h"

EnergyStructure::EnergyStructure(Shader& textureShader,
                                 Shader& linesShader,
                                 std::unique_ptr<StructureView> view) :
  BuildableStructure(textureShader, linesShader, std::move(view))
{
}
