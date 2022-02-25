#pragma once

#include "view/SelectableView.h"

class StructureView : public SelectableView {
 public:
  StructureView(glm::vec3 position, float selectionRadius,
                HealthBarParams healthBarParams,
                fig::TexturePackType texturesType);

  void rotate(float degreeAngle);
  void move(glm::vec3 position);

 protected:
  void showHealthBar() override;
};
