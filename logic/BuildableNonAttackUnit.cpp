#include "BuildableNonAttackUnit.h"

BuildableNonAttackUnit::BuildableNonAttackUnit(Shader& textureShader,
                                               Shader& linesShader,
                                               std::unique_ptr<UnitView> view,
                                               AStar* router) :
  Buildable(textureShader, linesShader),
  Unit<BuildableNonAttackUnit>(router, view.get()), _view(std::move(view))
{
  _viewPtr = _view.get();
}
