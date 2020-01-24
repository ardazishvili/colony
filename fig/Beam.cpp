#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Beam.h"

Beam::Beam(Shader& shader,
           glm::vec3 begin,
           glm::vec3 end,
           float r,
           unsigned int numLines) :
  LinesObject(shader),
  _r(r), _numLines(numLines)
{
  _offset = begin;
  init(begin, end);
}

void Beam::render()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _offset);
  float angle = fmod(glfwGetTime(), 2 * M_PI) * _rotateSpeed;
  model = glm::rotate(model, _ozAngle, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::rotate(model, _oyAngle, glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);

  LinesObject::render();
}

void Beam::init(glm::vec3 begin, glm::vec3 end)
{
  auto deltaAngle = M_PI * 2 / _numLines;
  auto angleStep = M_PI * 2 / _fragmentsNum;
  auto rStep = _r / _fragmentsNum;
  auto ozDev = ::atan((end.z - begin.z) / ::sqrt(::pow(end.x - begin.x, 2) +
                                                 ::pow(end.y - begin.y, 2)));
  auto oyDev = ::atan((end.x - begin.x) / (end.y - begin.y));
  if ((end.x == begin.x) && (end.y == begin.y)) {
    oyDev = 0.0f;
  }
  _oyAngle = (M_PI / 2 - ::abs(ozDev));
  _ozAngle = M_PI / 2 - oyDev;

  if (end.y < begin.y) {
    _ozAngle += M_PI;
  }
  if (end.z < begin.z) {
    _oyAngle = -_oyAngle + M_PI;
  }
  auto height = ::sqrt(::pow(begin.x - end.x, 2) + ::pow(begin.y - end.y, 2) +
                       ::pow(begin.z - end.z, 2));
  auto zStep = height / (_fragmentsNum - 1);
  for (unsigned int i = 0; i < _numLines; ++i) {
    _i.push_back(i * _fragmentsNum);
    float r = _r;

    for (unsigned int j = 0; j < _fragmentsNum; ++j) {
      auto p1 = glm::vec3();
      p1.x = r * ::sin(angleStep * j + deltaAngle * i);
      p1.y = r * ::cos(angleStep * j + deltaAngle * i);
      p1.z = j * zStep;
      _v.push_back(p1);
      r -= rStep;

      _i.push_back(i * _fragmentsNum + j);
      _i.push_back(i * _fragmentsNum + j);
    }
    _i.push_back(i * _fragmentsNum + _fragmentsNum - 1);
  }

  LinesObject::initBuffers();
}
