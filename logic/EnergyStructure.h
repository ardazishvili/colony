#ifndef ENERGY_STRUCTURE_H
#define ENERGY_STRUCTURE_H

#include "GroundStructure.h"

class EnergyStructure : public GroundStructure
{

public:
  EnergyStructure(Shader& textureShader,
                  Shader& linesShader,
                  std::unique_ptr<StructureView> view);
};

#endif
