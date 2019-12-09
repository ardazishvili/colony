#ifndef BARRER_VIEW_H
#define BARRER_VIEW_H

#include "../engine/Model.h"
#include "../engine/Shader.h"
#include "View.h"

class BarrierView
{
public:
  BarrierView(Shader& textureShader, Shader& _colorShader, glm::vec3 position);
  void draw();
  glm::vec2 position() const;

private:
  std::shared_ptr<Model> _model;
  Shader& _textureShader;
  Shader& _colorShader;
  glm::vec3 _position;
  float _scaleFactor{ 1 };
};

#endif
