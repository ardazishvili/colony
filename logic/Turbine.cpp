#include <memory>

#include "Turbine.h"

#include "Game.h"

const int Turbine::TURBINE_HP = 200;

Turbine::Turbine(Shader& textureShader,
                 Shader& linesShader,
                 Game* game,
                 glm::vec3 position) :
  EnergyStructure(
    textureShader,
    linesShader,
    std::make_unique<TurbineView>(textureShader,
                                  linesShader,
                                  position,
                                  game->getNearestShroudPosition())),
  _game(game)
{
  _game->addBarrierPotential(this);
}

UnitBuilders Turbine::getUnitBuilders(Game* game)
{
  return UnitBuilders();
}

StructureBuilders Turbine::getStructureBuilders()
{
  return StructureBuilders();
}

void Turbine::commit()
{
  BuildableStructure::commit();
  // TODO downcast!
  TurbineView* v = dynamic_cast<TurbineView*>(_view.get());
  v->initBeam();
}
