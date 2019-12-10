#include "Sphere.h"

Sphere::Sphere(Shader& shader,
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

void Sphere::render()
{
  _shader.use();
  _shader.configure();
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _offset);
  model = glm::scale(model, glm::vec3(3.0f, 2.0f, 1.0f));
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);
  _mesh.render();
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
}
