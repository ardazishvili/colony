#include "VehicleGroup.h"

void VehicleGroup::add(BuildableUnit* unit)
{
  _selected.push_back(unit);
}

bool VehicleGroup::empty() const
{
  return _selected.empty();
}

void VehicleGroup::startShooting(Buildable* target)
{
  for (auto& vehicle : _selected) {
    vehicle->startShooting(target);
  }
}

void VehicleGroup::startMoving(glm::vec3 destination)
{
  for (auto& vehicle : _selected) {
    vehicle->startMoving(destination);
  }
}

void VehicleGroup::clear()
{
  _selected.clear();
}
