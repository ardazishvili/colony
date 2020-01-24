#ifndef SPHERE_H
#define SPHERE_H

#include "Shader.h"
#include "SphereMesh.h"

class Sphere
{

public:
  Sphere(Shader& shader,
         glm::vec3 center,
         float radius,
         unsigned int divisions);
  void render();

private:
  Shader& _shader;
  SphereMesh _mesh;
  glm::vec3 _offset{ glm::vec3(0.0f) };
};

#endif
