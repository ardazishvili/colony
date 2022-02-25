#pragma once

#include "logic/structures/GroundStructure.h"

class EnergyStructure : public GroundStructure {
 public:
  EnergyStructure(std::unique_ptr<StructureView> view);
};
