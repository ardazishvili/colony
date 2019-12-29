#ifndef PATH_H
#define PATH_H

#include "../math/AStar.h"
#include "LinesObject.h"

class Path : public LinesObject
{
public:
  Path(Shader& shader, AStar* router);
  void render();
  APath route() const;
  bool init(glm::vec3 s, glm::vec3 e);
  /* void setStart(glm::vec3 s); */

private:
  static const float Z_OFFSET;
  AStar* _router;
  APath _route;
};

std::shared_ptr<Path> makePath(Shader& shader,
                               AStar* router,
                               glm::vec3 s,
                               glm::vec3 e);

#endif
