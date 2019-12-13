#include "../imgui/imgui.h"

#include "../math/Noise.h"
#include "SphereMesh.h"
float color[3] = { 255.0f / 255, 143.0f / 255, 54.0f / 255 };

void SphereMesh::render()
{
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _indices.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void SphereMesh::init(float r, unsigned int divisions)
{
  ImGui::Begin("sphere noise");
  static float frequency_plain = 1.5;
  static float frequencyFactor_plain = 3.0;
  static float amplitudeFactor_plain = 0.325;
  ImGui::SetWindowPos(ImVec2(0, 340));
  ImGui::SetWindowSize(ImVec2(500, 110));
  ImGui::SliderFloat("frequency slider", &frequency_plain, 1.0f, 2.5f);
  ImGui::SliderFloat(
    "frequencyFactor slider", &frequencyFactor_plain, 0.0f, 3.0f);
  ImGui::SliderFloat(
    "amplitudeFactor slider", &amplitudeFactor_plain, 0.1f, 1.5f);
  ImGui::End();

  ImGui::Begin("sphere color");
  ImGui::SetWindowPos(ImVec2(0, 560));
  ImGui::SetWindowSize(ImVec2(200, 50));
  ImGui::ColorEdit3("color", color);
  ImGui::End();

  auto noise = Noise(777);
  unsigned int stacksNum = divisions;
  unsigned int sectorNum = divisions;
  _v.reserve(stacksNum * sectorNum);
  float stackStep = M_PI / stacksNum;
  float sectorStep = 2 * M_PI / sectorNum;
  float stackAngle, sectorAngle;
  for (unsigned int i = 0; i <= stacksNum; ++i) {
    stackAngle = M_PI / 2 - i * stackStep;
    auto tmp = r * ::cos(stackAngle);
    for (unsigned int j = 0; j <= sectorNum; ++j) {
      sectorAngle = j * sectorStep;
      auto v = VertexColor();
      v.p.x = tmp * ::cos(sectorAngle);
      v.p.y = tmp * ::sin(sectorAngle);
      auto dummy = glm::vec2();
      auto nv_plain = noise.fractal(glm::vec2(v.p.x, v.p.y),
                                    dummy,
                                    frequency_plain,
                                    frequencyFactor_plain,
                                    amplitudeFactor_plain,
                                    5);
      v.p.z = r * ::sin(stackAngle) + nv_plain;

      v.normal.x = v.p.x / r;
      v.normal.y = v.p.y / r;
      v.normal.z = v.p.z / r;

      v.color = glm::vec4(color[0], color[1], color[2], 0.4f);

      _v.push_back(v);
    }
  }

  _indices.reserve((stacksNum - 2) * sectorNum * 2 * 3 + 2 * sectorNum * 3);
  unsigned int k1, k2;
  for (unsigned int i = 0; i < stacksNum; ++i) {
    k1 = i * (sectorNum + 1);
    k2 = k1 + sectorNum + 1;
    for (unsigned int j = 0; j < sectorNum; ++j, ++k1, ++k2) {
      if (i != 0) {
        _indices.push_back(k1);
        _indices.push_back(k2);
        _indices.push_back(k1 + 1);
      }
      if (i != (stacksNum - 1)) {
        _indices.push_back(k1 + 1);
        _indices.push_back(k2);
        _indices.push_back(k2 + 1);
      }
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(
    GL_ARRAY_BUFFER, sizeof(VertexColor) * _v.size(), &_v[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        4,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(VertexColor),
                        (void*)offsetof(VertexColor, color));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(VertexColor),
                        (void*)offsetof(VertexColor, normal));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(_indices[0]) * _indices.size(),
               &_indices[0],
               GL_STATIC_DRAW);

  glBindVertexArray(0);
}
