#include "NonAttackUnit.h"

NonAttackUnit::NonAttackUnit(fig::Shader& textureShader,
                             fig::Shader& linesShader,
                             std::unique_ptr<UnitView> view,
                             fig::AStar* router) :
  Buildable(textureShader, linesShader, view.get()),
  Unit<NonAttackUnit>(router, view.get()), _view(std::move(view))
{
}
