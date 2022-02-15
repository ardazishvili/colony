#pragma once

#include "view/AttackUnitView.h"

class TankView : public AttackUnitView {
 public:
  TankView(glm::vec3 position, float tankTypeScaling);
  void draw() override;
  void move(glm::vec3 newPosition) override;
  void rotateBody(float degreeAngle) override;
  void rotateGun(float degreeAngle) override;

 private:
  void updateGun();

  float _targetGunAngle{1.001f};   // TODO animation issue
  float _currentGunAngle{0.001f};  // TODO animation issue
  float _tankTypeScaleFactor;
  static constexpr float TANK_GUN_ANGLE_INCREMENT = 1.5;
  static constexpr float TANK_GUN_ANGLE_TOLERANCE = 1.5;
  static constexpr float TANK_HEALTH_BAR_WIDTH = 0.5;
  static constexpr float TANK_HEALTH_BAR_HEIGHT = 0.04;
};
