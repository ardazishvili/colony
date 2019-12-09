#include "Circle.h"

Circle::Circle(Shader& shader,
               glm::vec3 center,
               float radius,
               unsigned int divisions) :
  _shader(shader)
{
  _mesh.init(radius, divisions);
  _offset.x = center.x;
  _offset.y = center.y;
  _offset.z = center.z;
}

void Circle::render()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _offset);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);
  _mesh.render();
}
