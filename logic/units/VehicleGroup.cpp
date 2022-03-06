#include "logic/units/VehicleGroup.h"

bool VehicleGroup::empty() const { return _selected.empty(); }

void VehicleGroup::startShooting(Buildable* target) {
  for (auto* vehicle : _selected) {
    vehicle->startShooting(target);
  }
}

void VehicleGroup::setRoute(glm::vec3 destination) {
  for (auto* vehicle : _selected) {
    vehicle->setRoute(destination);
  }
}

void VehicleGroup::clear() { _selected.clear(); }
