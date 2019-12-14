#ifndef BEAM_H
#define BEAM_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

using Points = std::vector<glm::vec3>;
class Beam
{
public:
  Beam(Shader& shader, glm::vec3 begin, glm::vec3 end);
  void init(glm::vec3 begin, glm::vec3 end);
  void render();

private:
  Shader& _shader;
  unsigned int _vao;
  unsigned int _vbo;
  Points _v;
  float _rotateSpeed{ 1.0f };
  unsigned int _fragmentsNum{ 30 };
  float _r{ 0.9 };
  unsigned int _numLines{ 5 };
  float _oxAngle;
  float _oyAngle;
};

#endif
