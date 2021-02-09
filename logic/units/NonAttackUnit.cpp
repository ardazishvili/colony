#include "NonAttackUnit.h"

NonAttackUnit::NonAttackUnit(std::unique_ptr<UnitView> view) :
  Buildable(view.get()), Unit<NonAttackUnit>(view.get()), _view(std::move(view))
{
}
