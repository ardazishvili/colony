#pragma once

#include "view/UnitView.h"

class AttackUnitView : public UnitView {
 public:
  AttackUnitView(glm::vec3 position, float selectionRadius,
                 HealthBarParams healthBarParams,
                 fig::TexturePackType texturesType);
  virtual void rotateGun(float degreeAngle) = 0;
};
