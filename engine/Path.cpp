#include "Path.h"
#include "../globals.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float Path::Z_OFFSET = 0.1;

Path::Path(Shader& shader) : LinesObject(shader)
{
  _v.push_back(glm::vec3());
  _v.push_back(glm::vec3());

  _i.push_back(0);
  _i.push_back(1);

  LinesObject::initBuffers();
}

void Path::render()
{
  logger.log("Path render");
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);

  LinesObject::render();
}

void Path::setStart(glm::vec3 s)
{
  s.z += Z_OFFSET;
  _v.at(0) = s;
  reloadData();
}

void Path::setEnd(glm::vec3 e)
{
  e.z += Z_OFFSET;
  _v.at(1) = e;
  reloadData();
}

void Path::reloadData()
{
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferSubData(GL_ARRAY_BUFFER,
                  sizeof(glm::vec3) * 0,
                  sizeof(glm::vec3) * _v.size(),
                  &_v[0]);
}
void Path::clear()
{
  _v.at(0) = glm::vec3();
  _v.at(1) = glm::vec3();
}
