#ifndef LINES_OBJECT_H
#define LINES_OBJECT_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

using Points = std::vector<glm::vec3>;
using Indices = std::vector<unsigned int>;
class LinesObject
{
public:
  LinesObject(Shader& shader);
  void initBuffers();
  void render();

protected:
  Shader& _shader;
  unsigned int _vao;
  unsigned int _vbo;
  unsigned int _ebo;
  Points _v;
  Indices _i;
};

#endif
