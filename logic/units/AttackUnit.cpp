#include "AttackUnit.h"

AttackUnit::AttackUnit(fig::Shader& textureShader,
                       fig::Shader& linesShader,
                       std::unique_ptr<AttackUnitView> view,
                       fig::AStar* router,
                       Shell::Size sh,
                       float speed) :
  Buildable(textureShader, linesShader, view.get()),
  Unit<AttackUnit>(router, view.get()), Attacking<AttackUnit>(textureShader, sh, view.get()),
  Moving<AttackUnit>(linesShader, view.get(), speed), Selectable<AttackUnit>(view.get()), _view(std::move(view))
{
}

void AttackUnit::render()
{
  Unit<AttackUnit>::render();
}
