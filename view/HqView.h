#pragma once

#include "view/StructureView.h"

class HqView : public StructureView {
 public:
  HqView(glm::vec3 position);
  void draw() override;

 private:
  static float HQ_HEALTH_BAR_WIDTH;
  static float HQ_HEALTH_BAR_HEIGHT;
};
