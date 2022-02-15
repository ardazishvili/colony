#pragma once

#include "logic/units/Unit.h"
#include "view/UnitView.h"

class NonAttackUnit : public Buildable, public Unit<NonAttackUnit> {
 public:
  NonAttackUnit(std::unique_ptr<UnitView> view, fig::AStar& router);

 protected:
  std::unique_ptr<UnitView> _view;
};
