#include "Path.h"
#include "../globals.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float Path::Z_OFFSET = 0.1;

Path::Path(Shader& shader, AStar* router) : LinesObject(shader), _router(router)
{
  _v.push_back(glm::vec3());
  _v.push_back(glm::vec3());

  _i.push_back(0);
  _i.push_back(1);

  LinesObject::initBuffers();
  clear();
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

void Path::setUp(glm::vec3 s, glm::vec3 e)
{
  s.z += Z_OFFSET;
  _v.push_back(s);
  e.z += Z_OFFSET;
  _v.push_back(e);
  auto route = _router->getPath(glm::vec2(s.x, s.y), glm::vec2(e.x, e.y));
  reloadData();
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
  _v.at(_v.size() - 1) = e;
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
  _v.clear();
}

bool Path::isSettedUp() const
{
  return !_v.empty();
}
