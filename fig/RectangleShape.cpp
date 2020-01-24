#include "RectangleShape.h"
#include "../fig/globals.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

RectangleShape::RectangleShape(Shader& shader, Camera& camera) :
  LinesObject(shader), _camera(camera)
{
  for (int i = 0; i < 4; ++i) {
    _v.push_back(glm::vec3());
  }
  _i.push_back(0);
  _i.push_back(1);
  _i.push_back(1);
  _i.push_back(2);
  _i.push_back(2);
  _i.push_back(3);
  _i.push_back(3);
  _i.push_back(0);

  LinesObject::initBuffers();
}

void RectangleShape::render()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);

  LinesObject::render();
}

void RectangleShape::init(glm::vec3 s, glm::vec3 e)
{
  auto l = glm::distance(s, e);

  float a = glm::radians(_camera.getYaw() - 90);
  float ey = -e.x * ::sin(a) + e.y * ::cos(a);
  float ex = e.x * ::cos(a) + e.y * ::sin(a);
  float sy = -s.x * ::sin(a) + s.y * ::cos(a);
  float sx = s.x * ::cos(a) + s.y * ::sin(a);
  float angle = ::atan((ey - sy) / ::abs(ex - sx));
  _v.at(0) = s;
  _v.at(1) = glm::vec3(
    s.x - ::sin(angle) * sin(a) * l, s.y + l * sin(angle) * cos(a), s.z);

  _v.at(2) = e;
  _v.at(3) = glm::vec3(
    e.x + ::sin(angle) * sin(a) * l, e.y - l * sin(angle) * cos(a), e.z);

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferSubData(GL_ARRAY_BUFFER,
                  sizeof(glm::vec3) * 0,
                  sizeof(glm::vec3) * _v.size(),
                  &_v[0]);
}

void RectangleShape::setStart(glm::vec3 start)
{
  init(start, start);
}

void RectangleShape::setEnd(glm::vec3 end)
{
  init(_v.at(0), end);
}

void RectangleShape::clear()
{
  init(glm::vec3(), glm::vec3());
}

Points RectangleShape::getPoints() const
{
  return _v;
}

glm::vec2 RectangleShape::bottomLeft() const
{
  return glm::vec2(_v.at(0).x, _v.at(0).y);
}

glm::vec2 RectangleShape::topRight() const
{
  return glm::vec2(_v.at(2).x, _v.at(2).y);
}
