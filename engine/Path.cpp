#include "Path.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Path::Path(Shader& shader) : LinesObject(shader)
{
}

void Path::render()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);

  LinesObject::render();
}

void Path::setStart(glm::vec3 s)
{
  _s = s;
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferSubData(GL_ARRAY_BUFFER,
                  sizeof(glm::vec3) * 0,
                  sizeof(glm::vec3) * _v.size(),
                  &_v[0]);
}
