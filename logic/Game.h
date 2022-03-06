#pragma once

#include <memory>
#include <vector>

#include "fig/Terrain.h"
#include "helpers/aliases.h"
#include "logic/Control.h"
#include "logic/structures/AbstractPlant.h"
#include "logic/structures/EnergyStructure.h"
#include "logic/structures/Shroud.h"
#include "logic/units/AttackUnit.h"
#include "logic/units/VehicleGroup.h"

class Tank;
class AbstractStructureBuilder;

using Shrouds = std::vector<std::unique_ptr<Shroud>>;

class Game {
 public:
  void tick();
  void addTank(std::unique_ptr<Tank> tank);
  void addTankAndDestination(std::unique_ptr<Tank> tank, glm::vec3 destination);
  void addStructure(std::unique_ptr<GroundStructure> buildable);
  void addShroud(std::unique_ptr<Shroud> shroud);
  void addPlant(std::shared_ptr<AbstractPlant> plant);
  void addTerrain(fig::Terrain* terrain);
  void setControl(std::unique_ptr<Control> control);

  AttackUnit* getAttackUnit(const glm::vec3& mousePoint, bool select = false);
  VehicleGroup getVehicleGroup(fig::Points area);
  Buildable* getStructure(const glm::vec3& mousePoint);
  void clearPanel(Panel::Type type);
  bool panelIsEmpty(Panel::Type type);
  glm::vec3 getNearestShroudPositionFlat(glm::vec3 p) const;
  glm::vec3 getNearestShroudPositionGlobe(glm::vec3 p) const;
  void addBarrierPotential(EnergyStructure* es);

 private:
  Shroud* getNearestShroud(glm::vec3 p) const;

  AttackUnits _attack_units;
  Structures _structures;
  Shrouds _shrouds;
  Plants _plants;
  std::unique_ptr<Control> _control;
  AttackUnit* _selectedAttackUnit = nullptr;
  GroundStructure* _selectedStructure = nullptr;
  fig::Terrain* _terrain;
};
