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
  glm::mat4 flatModel() const;
  glm::mat4 globeModel() const;

protected:
  bool _hasAnimation{ false };
  std::shared_ptr<Model> _model;
  Shader& _shader;
  glm::vec3 _position;
  float _angle{ 0.0f };
  float _objScale{ 1.0f };

  static const float R;
  static const float S;
};

#endif
