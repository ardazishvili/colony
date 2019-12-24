#ifndef RECTANGLE_SHAPE_H
#define RECTANGLE_SHAPE_H

#include "LinesObject.h"

class RectangleShape : public LinesObject
{
public:
  RectangleShape(Shader& shader, Camera& camera);
  void render();
  void setStart(glm::vec3 start);
  void setEnd(glm::vec3 end);
  void clear();

  // start from bottom left -> clockwise
  Points getPoints() const;
  glm::vec2 bottomLeft() const;
  glm::vec2 topRight() const;

private:
  void init(glm::vec3 start, glm::vec3 end);

  Camera& _camera;
};

#endif
