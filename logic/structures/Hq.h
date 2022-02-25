#pragma once

#include "fig/Terrain.h"
#include "fig/math/AStar.h"
#include "logic/structures/GroundStructure.h"
#include "view/HqView.h"

struct AStar;
class Hq : public GroundStructure {
 public:
  Hq() = delete;
  Hq(ColonyEventManager* eventManager, fig::AStar& router, glm::vec3 position,
     fig::Terrain& terrain);

  UnitBuilders getUnitBuilders() override;
  StructureBuilders getStructureBuilders() override;

 private:
  ColonyEventManager* _eventManager;
  fig::Terrain& _terrain;
  fig::AStar& _router;
  static const int HQ_HP;
};
