#include "../imgui/imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Beam.h"

float verts[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
                  -0.5f, 0.5f,  0.0f, 0.5f, 0.5f,  0.0f };

Beam::Beam(Shader& shader, glm::vec3 begin, glm::vec3 end) : _shader(shader)
{
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenBuffers(1, &_vbo);

  _offset = begin;
  _offset.z = 0;
  if (begin.z > end.z) {
    _reverse = true;
  }
  init(begin, end);
}

void Beam::render()
{
  /* ImGui::Begin("beam angles"); */
  /* static float x = 0.0; */
  /* static float y = 0.0; */
  /* ImGui::SetWindowPos(ImVec2(0, 810)); */
  /* ImGui::SetWindowSize(ImVec2(500, 100)); */
  /* ImGui::SliderFloat("OX angle", &x, -M_PI, M_PI); */
  /* ImGui::SliderFloat("OY angle", &y, -M_PI, M_PI); */
  /* ImGui::End(); */
  _shader.use();
  _shader.configure();
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _offset);
  float angle = fmod(glfwGetTime(), 2 * M_PI) * _rotateSpeed;
  model = glm::rotate(model, _oxAngle, glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, _oyAngle, glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(
    GL_ARRAY_BUFFER, sizeof(glm::vec3) * _v.size(), &_v[0], GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(_vao);
  glDrawArrays(GL_LINES, 0, _v.size());

  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
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
}
