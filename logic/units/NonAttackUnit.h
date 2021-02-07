#ifndef NON_ATTACK_UNIT_H
#define NON_ATTACK_UNIT_H

#include "../../view/UnitView.h"
#include "Unit.h"

class NonAttackUnit
  : public Buildable
  , public Unit<NonAttackUnit>
{
public:
  NonAttackUnit(std::unique_ptr<UnitView> view, fig::AStar* router);

protected:
  std::unique_ptr<UnitView> _view;
};

#endif
