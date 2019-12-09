#ifndef PLANT_VIEW_H
#define PLANT_VIEW_H

#include "../engine/Model.h"
#include "../engine/Shader.h"
#include "View.h"

class PlantView
{
public:
  PlantView(Shader& shader, glm::vec3 position);
  void draw();

private:
  std::shared_ptr<Model> _model;
  Shader& _shader;
  glm::vec3 _position;
  float _scaleFactor{ 1.0f };
};

#endif
