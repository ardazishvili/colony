#pragma once

#include <glm/glm.hpp>

#include "fig/Terrain.h"
#include "helpers/aliases.h"
#include "logic/structures/AbstractPlant.h"
#include "logic/structures/EnergyStructure.h"
#include "logic/structures/Shroud.h"
#include "view/BarrierView.h"

using EnergyStructures = std::vector<EnergyStructure*>;
class Barrier : public EnergyStructure {
 public:
  Barrier(glm::vec3 position, fig::Terrain& terrain, fig::AStar& router);
  void render() override;
  UnitBuilders getUnitBuilders() override;
  StructureBuilders getStructureBuilders() override;
  void addPlant(std::shared_ptr<AbstractPlant> p);
  void addEnergyStructure(EnergyStructure* es);
  void commit() override;
  float radius() const;
  std::shared_ptr<Shroud> shroud();

 private:
  Shroud _shroud;

  float _radius{1.0f};
  fig::Terrain& _terrain;
  std::shared_ptr<fig::LivingArea> _livingArea{nullptr};
  EnergyStructures _energyStructures;
  Plants _plants;
  Timer _clock;
  std::chrono::milliseconds _bioUpdateTime{1000};
  static const int BARRIER_HP;
};
