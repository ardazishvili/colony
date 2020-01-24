#ifndef BEAM_H
#define BEAM_H

#include "LinesObject.h"

class Beam : public LinesObject
{
public:
  Beam(Shader& shader,
       glm::vec3 begin,
       glm::vec3 end,
       float r,
       unsigned int numLines);
  void render();

private:
  void init(glm::vec3 begin, glm::vec3 end);

  float _rotateSpeed{ 8.0f };
  unsigned int _fragmentsNum{ 10 };
  float _r;
  unsigned int _numLines;
  float _ozAngle;
  float _oyAngle;
  glm::vec3 _offset;
};

#endif
