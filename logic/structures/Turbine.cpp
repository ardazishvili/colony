#include "Turbine.h"
#include "../Game.h"

const int Turbine::TURBINE_HP = 200;

Turbine::Turbine(fig::Shader& textureShader, fig::Shader& linesShader, Game* game, glm::vec3 position) :
  EnergyStructure(textureShader,
                  linesShader,
                  std::make_unique<TurbineView>(textureShader,
                                                linesShader,
                                                position,
                                                game->getNearestShroudPositionFlat(position),
                                                game->getNearestShroudPositionGlobe(position))),
  _game(game)
{
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
  Structure<GroundStructure>::commit();
  // TODO downcast!
  TurbineView* v = dynamic_cast<TurbineView*>(_view.get());
  v->initBeam();
  _game->addBarrierPotential(this);
}
