#pragma once

#include "logic/concepts/Attacking.h"
#include "logic/concepts/Moving.h"
#include "logic/concepts/Selectable.h"
#include "logic/units/Unit.h"
#include "view/AttackUnitView.h"

class AttackUnit : public Buildable,
                   public Unit<AttackUnit>,
                   public Attacking<AttackUnit>,
                   public Moving<AttackUnit>,
                   public Selectable<AttackUnit> {
 public:
  AttackUnit(std::unique_ptr<AttackUnitView> view, fig::AStar& router,
             Shell::Size sh, float speed);
  void render() override;

 protected:
  friend Attacking;
  friend Moving;
  friend Selectable;
  std::unique_ptr<AttackUnitView> _view;
};
