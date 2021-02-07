#include "AttackUnit.h"

AttackUnit::AttackUnit(std::unique_ptr<AttackUnitView> view, fig::AStar* router, Shell::Size sh, float speed) :
  Buildable(view.get()), Unit<AttackUnit>(router, view.get()), Attacking<AttackUnit>(sh, view.get()),
  Moving<AttackUnit>(view.get(), speed), Selectable<AttackUnit>(view.get()), _view(std::move(view))
{
}

void AttackUnit::render()
{
  Unit<AttackUnit>::render();
}
