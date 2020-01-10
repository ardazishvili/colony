#include "BuildableAttackUnit.h"

BuildableAttackUnit::BuildableAttackUnit(Shader& textureShader,
                                         Shader& linesShader,
                                         std::unique_ptr<AttackUnitView> view,
                                         AStar* router,
                                         Shell::Size sh,
                                         float speed) :
  BuildableUnit(textureShader, linesShader, router),
  Attacking<BuildableAttackUnit>(textureShader, sh, view.get()),
  Moving<BuildableAttackUnit>(linesShader, view.get(), speed),
  _view(std::move(view))
{
  _viewPtr = _view.get();
}

