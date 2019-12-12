#ifndef TANK_FACTORY_VIEW_H
#define TANK_FACTORY_VIEW_H

#include "../logic/Buildable.h"
#include "SelectableView.h"

class TankFactoryView : public SelectableView
{
public:
  TankFactoryView(Shader& shader, glm::vec3 position);
  void draw() override;
  void rotate(float degreeAngle);
  void move(glm::vec3 position);
  void setTexture(Status status);
  float angle() const;

private:
  void showHealthBar();

  TexturePackType _texturesType;
  float _angle{ 0.0f };
  static float TANK_FACTORY_HEALTH_BAR_WIDTH;
  static float TANK_FACTORY_HEALTH_BAR_HEIGHT;
};

#endif
