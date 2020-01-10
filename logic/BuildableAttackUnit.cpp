#include "BuildableAttackUnit.h"

BuildableAttackUnit::BuildableAttackUnit(Shader& textureShader,
                                         Shader& linesShader,
                                         std::unique_ptr<AttackUnitView> view,
                                         AStar* router) :
  BuildableUnit(textureShader, linesShader, router),
  _view(std::move(view))
{
  _viewPtr = _view.get();
}

