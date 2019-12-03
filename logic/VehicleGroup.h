#ifndef VEHICLE_GROUP_H
#define VEHICLE_GROUP_H

#include <vector>

#include "Tank.h"

class VehicleGroup
{
public:
  VehicleGroup() = default;
  void add(BuildableUnit* unit);
  bool empty() const;
  void startShooting(Buildable* target);
  void startMoving(glm::vec2 destination);
  void clear();

private:
  using Selected = std::vector<BuildableUnit*>;
  Selected _selected;
};

#endif
