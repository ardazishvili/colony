#include "Barrier.h"

#include <memory>

#include "fig/globals.h"
#include "logic/builders/PlantBuilder.h"
#include "logic/builders/TreeBuilder.h"

const int Barrier::BARRIER_HP = 200;

Barrier::Barrier(glm::vec3 position, fig::Terrain& terrain, fig::AStar& router)
    : EnergyStructure(std::make_unique<BarrierView>(position, &terrain)),
      _shroud(router, position, *this),
      _terrain(terrain) {
  _health = BARRIER_HP;
  _maxHealth = _health;
}

void Barrier::render() {
  if (_stage == BuildStage::Done) {
    _shroud.render();
    if (_shroud.setUp()) {
      Structure<GroundStructure>::render();
      if (_livingArea != nullptr) {
        if (_clock.elapsed() >= _bioUpdateTime) {
          fig::logger.log("updating area...");
          _terrain.updateLivingArea(_livingArea.get());
          _clock.reload();
        }
      }
    }
  } else {
    Structure<GroundStructure>::render();
  }
}

UnitBuilders Barrier::getUnitBuilders() {
  auto builders = UnitBuilders();
  builders.push_back(std::make_unique<PlantBuilder>(*this, _terrain));
  builders.push_back(std::make_unique<TreeBuilder>(*this, _terrain));

  return builders;
}

StructureBuilders Barrier::getStructureBuilders() {
  return StructureBuilders();
}

void Barrier::addPlant(std::shared_ptr<AbstractPlant> p) {
  _livingArea->plants.push_back(p->position());
  _plants.push_back(p);
}

void Barrier::commit() {
  auto p = _view->position();
  // TODO downcast
  BarrierView* v = dynamic_cast<BarrierView*>(_view.get());
  fig::CircularRegion r = {p.x, p.y, v->radius()};
  auto c = _terrain.getRgbColor(p.x, p.y);
  _livingArea = _terrain.addLivingArea(r, glm::vec4(c.x, c.y, c.z, 0.5));
  Structure<GroundStructure>::commit();
}

void Barrier::addEnergyStructure(EnergyStructure* es) {
  _energyStructures.push_back(es);
  // TODO downcast
  BarrierView* v = dynamic_cast<BarrierView*>(_view.get());
  v->grow(_livingArea.get());
}

float Barrier::radius() const {
  // TODO downcast
  BarrierView* v = dynamic_cast<BarrierView*>(_view.get());
  return v->radius();
}

std::unique_ptr<Shroud> Barrier::shroud() {
  return std::unique_ptr<Shroud>(&_shroud);
}
