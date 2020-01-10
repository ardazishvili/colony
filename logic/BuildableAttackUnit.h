#ifndef BUILDABLE_ATTACK_UNIT_H
#define BUILDABLE_ATTACK_UNIT_H

#include "../view/AttackUnitView.h"
#include "Attacking.h"
#include "BuildableUnit.h"

class BuildableAttackUnit
  : public BuildableUnit
  , public Attacking<BuildableAttackUnit>
{
public:
  BuildableAttackUnit(Shader& textureShader,
                      Shader& linesShader,
                      std::unique_ptr<AttackUnitView> view,
                      AStar* router,
                      Shell::Size sh);
  /* virtual void startShooting(Buildable* other) = 0; */
  /* virtual void shootTarget() = 0; */
  /* virtual void stopShooting() = 0; */
  /* virtual bool isShooting() = 0; */
  virtual void startMoving(glm::vec2 endPoint) = 0;
  virtual void setRoute(glm::vec3 endPoint) = 0;

protected:
  friend Attacking;
  std::unique_ptr<AttackUnitView> _view;
};

#endif
