#include "logic/structures/Turbine.h"

#include "logic/Game.h"

const int Turbine::TURBINE_HP = 200;

Turbine::Turbine(Game& game, glm::vec3 position)
    : EnergyStructure(std::make_unique<TurbineView>(
          position, game.getNearestShroudPositionFlat(position),
          game.getNearestShroudPositionGlobe(position))),
      _game(game) {}

UnitBuilders Turbine::getUnitBuilders() { return UnitBuilders(); }

StructureBuilders Turbine::getStructureBuilders() {
  return StructureBuilders();
}

void Turbine::commit() {
  Structure<GroundStructure>::commit();
  // TODO downcast!
  TurbineView* v = dynamic_cast<TurbineView*>(_view.get());
  v->initBeam();
  _game.addBarrierPotential(this);
}
