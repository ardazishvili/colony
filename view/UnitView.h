#pragma once

#include "view/SelectableView.h"

class UnitView : public SelectableView {
 public:
  UnitView(glm::vec3 position, float selectionRadius,
           HealthBarParams healthBarParams, fig::TexturePackType texturesType);
  virtual void move(glm::vec3 newPosition) = 0;
  virtual void rotateBody(float degreeAngle) = 0;
  void showHealthBar() override;
};
