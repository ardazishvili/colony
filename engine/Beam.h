#ifndef BEAM_H
#define BEAM_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

using Points = std::vector<glm::vec3>;
class Beam
{
public:
  Beam(Shader& shader, unsigned int numPoints, float height);
  void init(unsigned int numPoints, float height);
  void render();

private:
  Shader& _shader;
  unsigned int _vao;
  unsigned int _vbo;
  Points _v;
  float _rotateSpeed{ 8.0f };
  unsigned int _fragmentsNum{ 3 };
  float _r{ 0.01 };
};

#endif
