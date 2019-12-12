#ifndef HQ_VIEW_H
#define HQ_VIEW_H

#include "../logic/Buildable.h"
#include "SelectableView.h"

class HqView : public SelectableView
{
public:
  HqView(Shader& shader, glm::vec3 position);
  void draw() override;
  void rotate(float degreeAngle);
  void move(glm::vec3 position);
  void setTexture(Status status);
  float angle() const;

private:
  void showHealthBar();

  TexturePackType _texturesType;
  float _angle{ 0.0f };
  static float HQ_HEALTH_BAR_WIDTH;
  static float HQ_HEALTH_BAR_HEIGHT;
};

#endif
