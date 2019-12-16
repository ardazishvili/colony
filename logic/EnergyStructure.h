#ifndef ENERGY_STRUCTURE_H
#define ENERGY_STRUCTURE_H

#include "BuildableStructure.h"

class EnergyStructure : public BuildableStructure
{

public:
  EnergyStructure(Shader& textureShader,
                  Shader& linesShader,
                  std::unique_ptr<StructureView> view);

protected:
  Shader& _linesShader;
};

#endif
