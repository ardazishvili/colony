#ifndef ATTACK_UNIT_H
#define ATTACK_UNIT_H

#include "../view/AttackUnitView.h"
#include "Unit.h"
#include "concepts/Attacking.h"
#include "concepts/Moving.h"
#include "concepts/Selectable.h"

class AttackUnit
  : public Buildable
  , public Unit<AttackUnit>
  , public Attacking<AttackUnit>
  , public Moving<AttackUnit>
  , public Selectable<AttackUnit>
{
public:
  AttackUnit(fig::Shader& textureShader,
             fig::Shader& linesShader,
             std::unique_ptr<AttackUnitView> view,
             fig::AStar* router,
             Shell::Size sh,
             float speed);
  void render() override;

protected:
  friend Attacking;
  friend Moving;
  friend Selectable;
  std::unique_ptr<AttackUnitView> _view;
};

#endif
