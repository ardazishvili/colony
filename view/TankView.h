#ifndef TANK_VIEW_H
#define TANK_VIEW_H

/* #include "../engine/Model.h" */
/* #include "../engine/Shader.h" */
#include "../engine/Surface.h"
#include "../logic/Buildable.h"
#include "SelectableView.h"
#include <GL/glew.h>

class TankView : public SelectableView
{
public:
  TankView(Shader& shader, glm::vec3 position, float tankTypeScaling);
  void draw() override;
  /* bool contain(glm::vec3 point) const; */
  void move(glm::vec3 newPosition);
  void rotateBody(float degreeAngle);
  void rotateGun(float degreeAngle);
  void setTexture(Status status);
  void setHealthBarScaleFactor(float factor);

private:
  void updateGun();
  void showHealthBar();

  TexturePackType _texturesType;
  float _bodyAngle{ 0.0f };
  float _targetGunAngle{ 0.001f };  // TODO animation issue
  float _currentGunAngle{ 0.001f }; // TODO animation issue
  Surface _healthBar;
  float _healthBarScaleFactor{ 1.0 };
  float _tankSizeScaleFactor;
  static float TANK_GUN_ANGLE_INCREMENT;
  static float TANK_GUN_ANGLE_TOLERANCE;
  static float TANK_HEALTH_BAR_WIDTH;
  static float TANK_HEALTH_BAR_HEIGHT;
};

#endif
