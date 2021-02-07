#ifndef ENERGY_STRUCTURE_H
#define ENERGY_STRUCTURE_H

#include "GroundStructure.h"

class EnergyStructure : public GroundStructure
{

public:
  EnergyStructure(std::unique_ptr<StructureView> view);
};

#endif
