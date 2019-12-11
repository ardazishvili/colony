#ifndef BARRER_VIEW_H
#define BARRER_VIEW_H

#include "../engine/Model.h"
#include "../engine/Shader.h"
#include "../engine/Surface.h"
#include "../engine/Terrain.h"
#include "../logic/Buildable.h"
#include "View.h"

class BarrierView
{
public:
  BarrierView(Shader& textureShader,
              Shader& _colorShader,
              glm::vec3 position,
              Terrain* terrain);
  void draw();
  glm::vec3 position() const;
  bool contain(glm::vec3 point) const;
  void setTexture(Status status);
  void setHealthBarScaleFactor(float factor);

private:
  void showHealthBar();

  std::shared_ptr<Model> _model;
  Shader& _textureShader;
  Shader& _colorShader;
  glm::vec3 _position;
  float _scaleFactor{ 1 };
  Surface _healthBar;
  float _healthBarScaleFactor{ 1.0 };
  Terrain* _terrain;
  static float BARRIER_HEALTH_BAR_WIDTH;
  static float BARRIER_HEALTH_BAR_HEIGHT;
};

#endif
