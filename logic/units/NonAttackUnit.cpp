#include "NonAttackUnit.h"

NonAttackUnit::NonAttackUnit(std::unique_ptr<UnitView> view, fig::AStar* router) :
  Buildable(view.get()), Unit<NonAttackUnit>(router, view.get()), _view(std::move(view))
{
}
