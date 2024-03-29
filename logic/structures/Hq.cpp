#include "logic/structures/Hq.h"

#include "figImpl/ColonyEventManager.h"
#include "logic/builders/BarrierBuilder.h"
#include "logic/builders/TankFactoryBuilder.h"
#include "logic/builders/TurbineBuilder.h"

const int Hq::HQ_HP = 500;

Hq::Hq(ColonyEventManager* eventManager, fig::AStar& router, glm::vec3 position,
       fig::Terrain& terrain)
    : GroundStructure(std::make_unique<HqView>(position)),
      _eventManager(eventManager),
      _terrain(terrain),
      _router(router) {
  _health = HQ_HP;
  _maxHealth = _health;
}

UnitBuilders Hq::getUnitBuilders() { return UnitBuilders(); }

StructureBuilders Hq::getStructureBuilders() {
  StructureBuilders builders = StructureBuilders();
  builders.push_back(
      std::make_unique<TankFactoryBuilder>(_eventManager, _router));

  builders.push_back(
      std::make_unique<BarrierBuilder>(_eventManager, _terrain, _router));

  builders.push_back(std::make_unique<TurbineBuilder>(_eventManager));

  return builders;
}
