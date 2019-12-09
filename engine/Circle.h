#ifndef CIRCLE_H
#define CIRCLE_H

#include "CircleMesh.h"
#include "Shader.h"

class Circle
{
public:
  Circle(Shader& shader,
         glm::vec3 center,
         float radius,
         unsigned int divisions);
  void render();

private:
  Shader& _shader;
  CircleMesh _mesh;
  glm::vec3 _offset{ glm::vec3(0.0f) };
};

#endif
