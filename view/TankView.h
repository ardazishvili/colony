#ifndef TANK_VIEW_H
#define TANK_VIEW_H

#include "UnitView.h"

class TankView : public UnitView
{
public:
  TankView(Shader& shader, glm::vec3 position, float tankTypeScaling);
  void draw() override;
  void move(glm::vec3 newPosition) override;
  void rotateBody(float degreeAngle);
  void rotateGun(float degreeAngle);

private:
  void updateGun();
  /* void showHealthBar(); */

  float _bodyAngle{ 0.0f };
  float _targetGunAngle{ 0.001f };  // TODO animation issue
  float _currentGunAngle{ 0.001f }; // TODO animation issue
  float _tankTypeScaleFactor;
  static float TANK_GUN_ANGLE_INCREMENT;
  static float TANK_GUN_ANGLE_TOLERANCE;
  static float TANK_HEALTH_BAR_WIDTH;
  static float TANK_HEALTH_BAR_HEIGHT;
};

#endif
