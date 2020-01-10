#include "BuildableAttackUnit.h"

BuildableAttackUnit::BuildableAttackUnit(Shader& textureShader,
                                         Shader& linesShader,
                                         std::unique_ptr<AttackUnitView> view,
                                         AStar* router,
                                         Shell::Size sh,
                                         float speed) :
  Buildable(textureShader, linesShader),
  Unit<BuildableAttackUnit>(router, view.get()), Attacking<BuildableAttackUnit>(
                                                   textureShader,
                                                   sh,
                                                   view.get()),
  Moving<BuildableAttackUnit>(linesShader, view.get(), speed),
  Selectable<BuildableAttackUnit>(view.get()), _view(std::move(view))
{
  _viewPtr = _view.get();
}

void BuildableAttackUnit::render()
{
  Unit<BuildableAttackUnit>::render();
}
