#ifndef HQ_VIEW_H
#define HQ_VIEW_H

/* #include "../engine/Model.h" */
/* #include "../engine/Shader.h" */
#include "../engine/Surface.h"
#include "../logic/Buildable.h"
#include "View.h"

class HqView : public View
{
public:
  HqView(Shader& shader, glm::vec3 position);
  void draw() override;
  bool contain(glm::vec3 point) const;
  glm::vec3 position() const override;
  void rotate(float degreeAngle);
  void move(glm::vec3 position);
  void setTexture(Status status);
  void setHealthBarScaleFactor(float factor);
  float angle() const;

private:
  void showHealthBar();

  /* std::shared_ptr<Model> _model; */
  TexturePackType _texturesType;
  /* Shader& _shader; */
  /* glm::vec3 _position; */
  float _angle{ 0.0f };
  Surface _healthBar;
  float _healthBarScaleFactor{ 1.0 };
  static float HQ_HEALTH_BAR_WIDTH;
  static float HQ_HEALTH_BAR_HEIGHT;
};

#endif
