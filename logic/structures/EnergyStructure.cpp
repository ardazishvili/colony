#include "EnergyStructure.h"

EnergyStructure::EnergyStructure(std::unique_ptr<StructureView> view) : GroundStructure(std::move(view))
{
}
