#ifndef ATTACK_UNIT_H
#define ATTACK_UNIT_H

#include "../../view/AttackUnitView.h"
#include "../concepts/Attacking.h"
#include "../concepts/Moving.h"
#include "../concepts/Selectable.h"
#include "Unit.h"

class AttackUnit
  : public Buildable
  , public Unit<AttackUnit>
  , public Attacking<AttackUnit>
  , public Moving<AttackUnit>
  , public Selectable<AttackUnit>
{
public:
  AttackUnit(std::unique_ptr<AttackUnitView> view, Shell::Size sh, float speed);
  void render() override;

protected:
  friend Attacking;
  friend Moving;
  friend Selectable;
  std::unique_ptr<AttackUnitView> _view;
};

#endif
