#include "NonAttackUnit.h"

NonAttackUnit::NonAttackUnit(Shader& textureShader,
                             Shader& linesShader,
                             std::unique_ptr<UnitView> view,
                             AStar* router) :
  Buildable(textureShader, linesShader, view.get()),
  Unit<NonAttackUnit>(router, view.get()), _view(std::move(view))
{
}
