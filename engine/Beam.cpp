#include "../imgui/imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Beam.h"

float verts[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
                  -0.5f, 0.5f,  0.0f, 0.5f, 0.5f,  0.0f };

Beam::Beam(Shader& shader,
           glm::vec3 begin,
           glm::vec3 end,
           float r,
           unsigned int numLines) :
  _shader(shader),
  _r(r), _numLines(numLines)
{
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenBuffers(1, &_vbo);

  _offset = begin;
  if (begin.z > end.z) {
    _reverse = true;
  }
  _offset.z = std::min(begin.z, end.z);
  init(begin, end);
}

void Beam::render()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _offset);
  float angle = fmod(glfwGetTime(), 2 * M_PI) * _rotateSpeed;
  model = glm::rotate(model, _oxAngle, glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, _oyAngle, glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);

  glBindVertexArray(_vao);
  glDrawArrays(GL_LINES, 0, _v.size());
}

void Beam::init(glm::vec3 begin, glm::vec3 end)
{
  auto deltaAngle = M_PI * 2 / _numLines;
  auto angleStep = M_PI * 2 / _fragmentsNum;
  auto rStep = _r / _fragmentsNum;
  _oyAngle = M_PI / 2 - ::atan((end.z - begin.z) / (end.x - begin.x));
  _oxAngle = -(M_PI / 2 - ::atan((end.z - begin.z) / (end.y - begin.y)));
  auto height = ::sqrt(::pow(begin.x - end.x, 2) + ::pow(begin.y - end.y, 2) +
                       ::pow(begin.z - end.z, 2));
  auto zStep = height / _fragmentsNum;
  for (unsigned int i = 0; i < _numLines; ++i) {
    float r = !_reverse ? _r : 0;
    for (unsigned int j = 0; j < _fragmentsNum; ++j) {
      auto p1 = glm::vec3();
      p1.x = r * ::sin(angleStep * j + deltaAngle * i);
      p1.y = r * ::cos(angleStep * j + deltaAngle * i);
      p1.z = j * zStep;
      _v.push_back(p1);

      r -= rStep;

      auto p2 = glm::vec3();
      p2.x = r * ::sin(angleStep * (j + 1) + deltaAngle * i);
      p2.y = r * ::cos(angleStep * (j + 1) + deltaAngle * i);
      p2.z = (j + 1) * zStep;
      _v.push_back(p2);
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(
    GL_ARRAY_BUFFER, sizeof(glm::vec3) * _v.size(), &_v[0], GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
  glEnableVertexAttribArray(0);
}
