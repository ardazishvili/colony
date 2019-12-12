#ifndef HQ_VIEW_H
#define HQ_VIEW_H

#include "../engine/Surface.h"
#include "../logic/Buildable.h"
#include "SelectableView.h"

class HqView : public SelectableView
{
public:
  HqView(Shader& shader, glm::vec3 position);
  void draw() override;
  /* bool contain(glm::vec3 point) const; */
  void rotate(float degreeAngle);
  void move(glm::vec3 position);
  void setTexture(Status status);
  void setHealthBarScaleFactor(float factor);
  float angle() const;

private:
  void showHealthBar();

  TexturePackType _texturesType;
  float _angle{ 0.0f };
  Surface _healthBar;
  float _healthBarScaleFactor{ 1.0 };
  static float HQ_HEALTH_BAR_WIDTH;
  static float HQ_HEALTH_BAR_HEIGHT;
};

#endif
