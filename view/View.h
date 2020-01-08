#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../engine/Model.h"

class View
{
public:
  static float VIEW_SCALE;
  View(Shader& shader, glm::vec3 position);
  virtual void draw() = 0;
  virtual glm::vec3 position() const;
  float longitude() const;
  float latitude() const;
  float h(float phi) const;
  float k(float phi) const;

protected:
  bool _hasAnimation{ false };
  std::shared_ptr<Model> _model;
  Shader& _shader;
  glm::vec3 _position;
};

#endif
