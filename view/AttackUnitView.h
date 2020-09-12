#ifndef ATTACK_UNIT_VIEW_H
#define ATTACK_UNIT_VIEW_H

#include "UnitView.h"

class AttackUnitView : public UnitView
{
public:
  AttackUnitView(fig::Shader& shader,
                 glm::vec3 position,
                 float selectionRadius,
                 HealthBarParams healthBarParams,
                 fig::TexturePackType texturesType);
  virtual void rotateGun(float degreeAngle) = 0;
};

#endif
