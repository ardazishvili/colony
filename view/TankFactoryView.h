#pragma once

#include "view/StructureView.h"

class TankFactoryView : public StructureView {
 public:
  TankFactoryView(glm::vec3 position);
  void draw() override;

 private:
  static float TANK_FACTORY_HEALTH_BAR_WIDTH;
  static float TANK_FACTORY_HEALTH_BAR_HEIGHT;
};
