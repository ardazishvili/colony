#ifndef BUILDABLE_ATTACK_UNIT_H
#define BUILDABLE_ATTACK_UNIT_H

#include "../view/AttackUnitView.h"
#include "BuildableUnit.h"

class BuildableAttackUnit : public BuildableUnit
{
public:
  BuildableAttackUnit(Shader& textureShader,
                      Shader& linesShader,
                      std::unique_ptr<AttackUnitView> view,
                      AStar* router);
  virtual void startShooting(Buildable* other) = 0;
  virtual void startMoving(glm::vec2 endPoint) = 0;
  virtual void setRoute(glm::vec3 endPoint) = 0;

protected:
  std::unique_ptr<AttackUnitView> _view;
};

#endif
