#include "BuildableNonAttackUnit.h"

BuildableNonAttackUnit::BuildableNonAttackUnit(Shader& textureShader,
                                               Shader& linesShader,
                                               std::unique_ptr<UnitView> view,
                                               AStar* router) :
  BuildableUnit(textureShader, linesShader, router),
  _view(std::move(view))
{
  _viewPtr = _view.get();
}
