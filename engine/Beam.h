#ifndef BEAM_H
#define BEAM_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

using Points = std::vector<glm::vec3>;
class Beam
{
public:
  Beam(Shader& shader,
       glm::vec3 begin,
       glm::vec3 end,
       float r,
       unsigned int numLines);
  void init(glm::vec3 begin, glm::vec3 end);
  void render();

private:
  Shader& _shader;
  unsigned int _vao;
  unsigned int _vbo;
  Points _v;
  float _rotateSpeed{ 8.0f };
  unsigned int _fragmentsNum{ 10 };
  float _r;
  unsigned int _numLines;
  float _ozAngle;
  float _oyAngle;
  glm::vec3 _offset;
  bool _reverse{ false };
};

template<typename T>
int sgn(T val)
{
  return (T(0) < val) - (val < T(0));
}

#endif
