#ifndef VEHICLE_GROUP_H
#define VEHICLE_GROUP_H

#include <vector>

#include "Tank.h"

class VehicleGroup
{
public:
  VehicleGroup() = default;
  void add(BuildableAttackUnit* unit);
  bool empty() const;
  void startShooting(Buildable* target);
  void setRoute(glm::vec3 destination);
  void clear();

private:
  using Selected = std::vector<BuildableAttackUnit*>;
  Selected _selected;
};

#endif
