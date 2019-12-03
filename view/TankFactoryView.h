#ifndef TANK_FACTORY_VIEW_H
#define TANK_FACTORY_VIEW_H

#include "../engine/Model.h"
#include "../engine/Shader.h"
#include "../engine/Surface.h"
#include "../logic/Buildable.h"
#include "View.h"

class TankFactoryView : public View
{
public:
  TankFactoryView(Shader& shader, glm::vec2 position);
  void draw();
  bool contain(glm::vec2 point) const;
  glm::vec2 position();
  void rotate(float degreeAngle);
  void move(glm::vec2 position);
  void setTexture(Status status);
  void setHealthBarScaleFactor(float factor);
  float angle() const;

private:
  void showHealthBar();

  std::shared_ptr<Model> _model;
  TexturePackType _texturesType;
  Shader& _shader;
  glm::vec3 _position;
  float _angle{ 0.0f };
  Surface _healthBar;
  float _healthBarScaleFactor{ 1.0 };
  static float TANK_FACTORY_HEALTH_BAR_WIDTH;
  static float TANK_FACTORY_HEALTH_BAR_HEIGHT;
};

#endif
