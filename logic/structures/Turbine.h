#pragma once

#include "logic/structures/EnergyStructure.h"
#include "view/TurbineView.h"

class Turbine : public EnergyStructure {
 public:
  Turbine(Game& game, glm::vec3 position);
  UnitBuilders getUnitBuilders() override;
  StructureBuilders getStructureBuilders() override;
  void commit() override;

 private:
  Game& _game;
  static const int TURBINE_HP;
};
