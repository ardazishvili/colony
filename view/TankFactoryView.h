#ifndef TANK_FACTORY_VIEW_H
#define TANK_FACTORY_VIEW_H

#include "StructureView.h"

class TankFactoryView : public StructureView
{
public:
  TankFactoryView(Shader& shader, glm::vec3 position);
  void draw() override;
  void rotate(float degreeAngle);
  void move(glm::vec3 position);
  float angle() const;

private:
  float _angle{ 0.0f };
  static float TANK_FACTORY_HEALTH_BAR_WIDTH;
  static float TANK_FACTORY_HEALTH_BAR_HEIGHT;
};

#endif
