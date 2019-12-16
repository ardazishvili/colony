#include "EnergyStructure.h"

EnergyStructure::EnergyStructure(Shader& textureShader,
                                 Shader& linesShader,
                                 std::unique_ptr<StructureView> view) :
  BuildableStructure(textureShader, std::move(view)),
  _linesShader(linesShader)
{
}
