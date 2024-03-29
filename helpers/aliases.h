#pragma once

#include <memory>
#include <vector>

class AttackUnit;
class GroundStructure;
class AbstractPlant;

using AttackUnits = std::vector<std::unique_ptr<AttackUnit>>;
using Structures = std::vector<std::unique_ptr<GroundStructure>>;
using Plants = std::vector<std::shared_ptr<AbstractPlant>>;
