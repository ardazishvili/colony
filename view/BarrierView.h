#ifndef BARRER_VIEW_H
#define BARRER_VIEW_H

#include "../engine/Model.h"
#include "../engine/Shader.h"
#include "View.h"

class BarrierView
{
public:
  BarrierView(Shader& shader, glm::vec3 position);
  void draw();

private:
  std::shared_ptr<Model> _model;
  Shader& _shader;
  glm::vec3 _position;
  float _scaleFactor{ 1 };
};

#endif
