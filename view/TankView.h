#ifndef TANK_VIEW_H
#define TANK_VIEW_H

#include "../engine/Model.h"
#include "../engine/Shader.h"
#include "../engine/Surface.h"
#include "../logic/Buildable.h"
#include "View.h"
#include <GL/glew.h>

class TankView : public View
{
public:
  TankView(Shader& shader, glm::vec2 position, float tankTypeScaling);
  void draw();
  bool contain(glm::vec2 point) const;
  glm::vec2 position();
  void move(glm::vec2 moveIncrement);
  void rotateBody(float degreeAngle);
  void rotateGun(float degreeAngle);
  void setTexture(Status status);
  void setHealthBarScaleFactor(float factor);

private:
  void updateGun();
  void showHealthBar();

  std::shared_ptr<Model> _model;
  TexturePackType _texturesType;
  Shader& _shader;
  glm::vec3 _position;
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
