#ifndef ATTACK_UNIT_VIEW_H
#define ATTACK_UNIT_VIEW_H

#include "UnitView.h"

class AttackUnitView : public UnitView
{
public:
  AttackUnitView(Shader& shader,
                 glm::vec3 position,
                 float selectionRadius,
                 HealthBarParams healthBarParams,
                 TexturePackType texturesType);
  virtual void rotateGun(float degreeAngle) = 0;
};

#endif
