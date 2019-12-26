#ifndef PATH_H
#define PATH_H

#include "../math/AStar.h"
#include "LinesObject.h"

class Path : public LinesObject
{
public:
  Path(Shader& shader, AStar* router);
  void render();
  void setUp(glm::vec3 s, glm::vec3 e);
  void setStart(glm::vec3 s);
  void setEnd(glm::vec3 e);
  void clear();
  bool isSettedUp() const;

private:
  void reloadData();
  static const float Z_OFFSET;
  AStar* _router;
};

#endif
