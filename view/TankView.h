#ifndef TANK_VIEW_H
#define TANK_VIEW_H

#include "AttackUnitView.h"

class TankView : public AttackUnitView
{
public:
  TankView(glm::vec3 position, float tankTypeScaling);
  void draw() override;
  void move(glm::vec3 newPosition) override;
  void rotateBody(float degreeAngle) override;
  void rotateGun(float degreeAngle) override;

private:
  void updateGun();

  float _targetGunAngle{ 1.001f };  // TODO animation issue
  float _currentGunAngle{ 0.001f }; // TODO animation issue
  float _tankTypeScaleFactor;
  static float TANK_GUN_ANGLE_INCREMENT;
  static float TANK_GUN_ANGLE_TOLERANCE;
  static float TANK_HEALTH_BAR_WIDTH;
  static float TANK_HEALTH_BAR_HEIGHT;
};

#endif
