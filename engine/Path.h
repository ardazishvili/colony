#ifndef PATH_H
#define PATH_H

#include "LinesObject.h"

class Path : public LinesObject
{
public:
  Path(Shader& shader);
  void render();
  void setStart(glm::vec3 s);

private:
  glm::vec3 _s;
  glm::vec3 _e;
};

#endif
