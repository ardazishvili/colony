#ifndef BUILDABLE_ATTACK_UNIT_H
#define BUILDABLE_ATTACK_UNIT_H

#include "../view/AttackUnitView.h"
#include "Attacking.h"
#include "BuildableUnit.h"
#include "Moving.h"

class BuildableAttackUnit
  : public BuildableUnit
  , public Attacking<BuildableAttackUnit>
  , public Moving<BuildableAttackUnit>
{
public:
  BuildableAttackUnit(Shader& textureShader,
                      Shader& linesShader,
                      std::unique_ptr<AttackUnitView> view,
                      AStar* router,
                      Shell::Size sh,
                      float speed);
  /* virtual void startMoving(glm::vec2 endPoint) = 0; */
  /* virtual void move() = 0; */
  /* virtual bool isMoving() = 0; */
  /* virtual void setRoute(glm::vec3 endPoint) = 0; */

protected:
  /* virtual void stopMoving() = 0; */

  friend Attacking;
  friend Moving;
  std::unique_ptr<AttackUnitView> _view;
};

#endif
