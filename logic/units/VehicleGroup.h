#pragma once

#include <memory>
#include <vector>

#include "logic/units/AttackUnit.h"
#include "logic/units/Tank.h"

class VehicleGroup {
 public:
  using Selected = std::vector<AttackUnit*>;

  VehicleGroup() = default;
  VehicleGroup(Selected c) : _selected(c){};
  void add(AttackUnit* unit) { _selected.push_back(unit); };
  bool empty() const;
  void startShooting(Buildable* target);
  void setRoute(glm::vec3 destination);
  void clear();

 private:
  Selected _selected;
};
