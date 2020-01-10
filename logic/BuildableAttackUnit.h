#ifndef BUILDABLE_ATTACK_UNIT_H
#define BUILDABLE_ATTACK_UNIT_H

#include "../view/AttackUnitView.h"
#include "Attacking.h"
#include "BuildableUnit.h"
#include "Moving.h"
#include "Selectable.h"

class BuildableAttackUnit
  : public Buildable
  , public Unit<BuildableAttackUnit>
  , public Attacking<BuildableAttackUnit>
  , public Moving<BuildableAttackUnit>
  , public Selectable<BuildableAttackUnit>
{
public:
  BuildableAttackUnit(Shader& textureShader,
                      Shader& linesShader,
                      std::unique_ptr<AttackUnitView> view,
                      AStar* router,
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
