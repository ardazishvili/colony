#ifndef TANK_FACTORY_VIEW_H
#define TANK_FACTORY_VIEW_H

#include "StructureView.h"

class TankFactoryView : public StructureView
{
public:
  TankFactoryView(Shader& shader, glm::vec3 position);
  void draw() override;

private:
  static float TANK_FACTORY_HEALTH_BAR_WIDTH;
  static float TANK_FACTORY_HEALTH_BAR_HEIGHT;
};

#endif
