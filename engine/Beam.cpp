#include "../imgui/imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Beam.h"

float verts[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
                  -0.5f, 0.5f,  0.0f, 0.5f, 0.5f,  0.0f };

Beam::Beam(Shader& shader, unsigned int numPoints, float height) :
  _shader(shader)
{
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenBuffers(1, &_vbo);

  init(numPoints, height);
}

void Beam::render()
{
  ImGui::Begin("beam angles");
  static float x = 0.0;
  static float y = 0.0;
  ImGui::SetWindowPos(ImVec2(0, 810));
  ImGui::SetWindowSize(ImVec2(500, 100));
  ImGui::SliderFloat("OX angle", &x, -M_PI, M_PI);
  ImGui::SliderFloat("OY angle", &y, -M_PI, M_PI);
  ImGui::End();
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  /* model = glm::translate(model, _offset * _xyScale); */
  float angle = fmod(glfwGetTime(), 2 * M_PI) * _rotateSpeed;
  model = glm::rotate(model, x, glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, y, glm::vec3(0.0f, 1.0f, 0.0f));
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
}

void Beam::init(unsigned int numPoints, float height)
{
  auto deltaAngle = M_PI * 2 / numPoints;
  auto angleStep = M_PI * 2 / _fragmentsNum;
  auto zStep = height / _fragmentsNum;
  for (unsigned int i = 0; i < numPoints; ++i) {
    for (unsigned int j = 0; j < _fragmentsNum - 1; ++j) {
      auto p1 = glm::vec3();
      p1.x = _r * ::sin(angleStep * j + deltaAngle * i);
      p1.y = _r * ::cos(angleStep * j + deltaAngle * i);
      p1.z = j * zStep;
      _v.push_back(p1);

      auto p2 = glm::vec3();
      p2.x = _r * ::sin(angleStep * (j + 1) + deltaAngle * i);
      p2.y = _r * ::cos(angleStep * (j + 1) + deltaAngle * i);
      p2.z = (j + 1) * zStep;
      _v.push_back(p2);
    }
  }
}
