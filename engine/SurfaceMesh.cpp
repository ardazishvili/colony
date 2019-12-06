#include <string>

#include "../imgui/imgui.h"

#include "../math/Noise.h"
#include "SurfaceMesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

struct RgbColor
{
  float r;
  float g;
  float b;
};

using HeightPart = float;
std::map<HeightPart, RgbColor> colorMapping = { { 0.0f, { 113, 128, 143 } },
                                                { 0.5f, { 237, 227, 143 } },
                                                { 1.0f, { 242, 127, 115 } } };

SurfaceMesh::SurfaceMesh()
{
  _vao = 0;
  _vertexVbo = 0;
  _indicesEbo = 0;
  deinit();

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glGenBuffers(1, &_vertexVbo);
  glGenBuffers(1, &_indicesEbo);
}

SurfaceMesh::~SurfaceMesh()
{
  deinit();
}

void SurfaceMesh::deinit()
{
  if (_vertexVbo != 0) {
    glDeleteBuffers(1, &_vertexVbo);
    glDeleteBuffers(1, &_indicesEbo);
  }

  if (_vao != 0) {
    glDeleteVertexArrays(1, &_vao);
    _vao = 0;
  }
}

void SurfaceMesh::render()
{
  glBindVertexArray(_vao);

  for (unsigned int i = 0; i < _meshesData.size(); i++) {
    glDrawElementsBaseVertex(
      GL_TRIANGLES,
      _meshesData[i].numIndices,
      GL_UNSIGNED_INT,
      (void*)(sizeof(unsigned int) * _meshesData[i].baseIndex),
      _meshesData[i].baseVertex);
  }

  glBindVertexArray(0);
}

void SurfaceMesh::initSurface(float bottomLeftX,
                              float bottomLeftY,
                              float topRightX,
                              float topRightY,
                              int divisions)
{
  _meshesData.resize(1);

  _meshesData[0].materialIndex = 0;
  _meshesData[0].numIndices = ::pow(divisions, 2) * 2 * 3;
  _meshesData[0].baseVertex = 0;
  _meshesData[0].baseIndex = 0;
  _meshesData[0].name = "surface";

  _v.reserve(::pow(divisions + 1, 2));
  float xStep = (topRightX - bottomLeftX) / divisions;
  float yStep = (topRightY - bottomLeftY) / divisions;

  ImGui::Begin("surface");
  static float frequency = 0.3;
  static float frequencyFactor = 2.0;
  static float amplitudeFactor = 0.6;
  static bool nh = true;
  ImGui::SetWindowPos(ImVec2(0, 0));
  ImGui::SetWindowSize(ImVec2(500, 110));
  ImGui::SliderFloat("frequency slider", &frequency, 0.0f, 1.5f);
  ImGui::SliderFloat("frequencyFactor slider", &frequencyFactor, 0.0f, 3.0f);
  ImGui::SliderFloat("amplitudeFactor slider", &amplitudeFactor, 0.3f, 1.5f);
  ImGui::Checkbox("no negative height", &nh);
  ImGui::End();
  auto noise = Noise(777);
  auto max = 0.0f;
  auto min = 0.0f;
  int width = divisions + 1;
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < width; ++j) {
      VertexNoColor vertex;
      vertex.p.x = bottomLeftX + static_cast<float>(i) * xStep;
      vertex.p.y = bottomLeftY + static_cast<float>(j) * yStep;
      glm::vec2 derivs;
      auto nv = noise.fractal(glm::vec2(vertex.p.x, vertex.p.y),
                              derivs,
                              frequency,
                              frequencyFactor,
                              amplitudeFactor,
                              5);
      max = std::max(max, nv);
      if (!nh) {
        min = std::min(min, nv);
        vertex.p.z = nv;
      } else {
        vertex.p.z = ::max(nv, 0.0f);
      }
      vertex.normal = glm::vec3(0.0f);

      _v.push_back(vertex);
      if (j != 0 && j != (width - 1)) {
        _v.push_back(vertex);
      }
    }
  }
  auto augmentedWidth = divisions + 1 + (divisions + 1 - 2);
  for (int i = 0; i < width - 1; ++i) {
    for (int j = 0; j < augmentedWidth; ++j) {
      glm::vec3 p0(0);
      glm::vec3 p1(0);
      glm::vec3 p2(0);
      if (i % 2 == 0) {
        if (j % 4 == 0) {
          p1 = _v.at(augmentedWidth * i + j + 1 + augmentedWidth).p;
          p2 = _v.at(augmentedWidth * i + j).p;
          p0 = _v.at(augmentedWidth * i + j + augmentedWidth).p;
        } else if (j % 4 == 1) {
          p1 = _v.at(augmentedWidth * i + j - 1).p;
          p2 = _v.at(augmentedWidth * i + j + augmentedWidth).p;
          p0 = _v.at(augmentedWidth * i + j).p;
        } else if (j % 4 == 2) {
          p1 = _v.at(augmentedWidth * i + j + augmentedWidth).p;
          p2 = _v.at(augmentedWidth * i + j + 1).p;
          p0 = _v.at(augmentedWidth * i + j).p;
        } else if (j % 4 == 3) {
          p1 = _v.at(augmentedWidth * i + j).p;
          p2 = _v.at(augmentedWidth * i + j - 1 + augmentedWidth).p;
          p0 = _v.at(augmentedWidth * i + j + augmentedWidth).p;
        }
      } else if (i % 2 == 1) {
        if (j % 4 == 0) {
          p1 = _v.at(augmentedWidth * i + j + augmentedWidth).p;
          p2 = _v.at(augmentedWidth * i + j + 1).p;
          p0 = _v.at(augmentedWidth * i + j).p;
        } else if (j % 4 == 1) {
          p1 = _v.at(augmentedWidth * i + j).p;
          p2 = _v.at(augmentedWidth * i + j - 1 + augmentedWidth).p;
          p0 = _v.at(augmentedWidth * i + j + augmentedWidth).p;
        } else if (j % 4 == 2) {
          p1 = _v.at(augmentedWidth * i + j + 1 + augmentedWidth).p;
          p2 = _v.at(augmentedWidth * i + j).p;
          p0 = _v.at(augmentedWidth * i + j + augmentedWidth).p;
        } else if (j % 4 == 3) {
          p1 = _v.at(augmentedWidth * i + j - 1).p;
          p2 = _v.at(augmentedWidth * i + j + augmentedWidth).p;
          p0 = _v.at(augmentedWidth * i + j).p;
        }
      }
      auto v1 = p1 - p0;
      auto v2 = p2 - p0;

      _v[augmentedWidth * i + j].normal = glm::cross(v1, v2);
      p0 = glm::vec3(0);
      p1 = glm::vec3(0);
      p2 = glm::vec3(0);
    }
  }
  auto amplitude = max - min;
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < augmentedWidth; ++j) {
      RgbColor a, b;
      auto h = _v[augmentedWidth * i + j].p.z / amplitude;
      if (h <= amplitude * 0.5) {
        a = colorMapping[0.0f];
        b = colorMapping[0.5f];
        h *= 2;
      } else {
        a = colorMapping[0.5f];
        b = colorMapping[1.0f];
      }
      _v[augmentedWidth * i + j].color.x = glm::lerp(a.r, b.r, h) / 255.0;
      _v[augmentedWidth * i + j].color.y = glm::lerp(a.g, b.g, h) / 255.0;
      _v[augmentedWidth * i + j].color.z = glm::lerp(a.b, b.b, h) / 255.0;
    }
  }
  _indices.reserve(::pow(divisions, 2) * 2 * 3);
  for (int i = 0; i < divisions; ++i) {
    for (int j = 0; j < divisions; ++j) {
      auto j2 = j * 2;
      if (((i % 2) + j) % 2 == 0) {
        _indices.push_back(i * augmentedWidth + j2);
        _indices.push_back(i * augmentedWidth + j2 + augmentedWidth);
        _indices.push_back(i * augmentedWidth + j2 + augmentedWidth + 1);

        _indices.push_back(i * augmentedWidth + j2 + 1);
        _indices.push_back(i * augmentedWidth + j2);
        _indices.push_back(i * augmentedWidth + j2 + augmentedWidth + 1);
      } else {
        _indices.push_back(i * augmentedWidth + j2);
        _indices.push_back(i * augmentedWidth + j2 + augmentedWidth);
        _indices.push_back(i * augmentedWidth + j2 + 1);

        _indices.push_back(i * augmentedWidth + j2 + 1);
        _indices.push_back(i * augmentedWidth + j2 + augmentedWidth);
        _indices.push_back(i * augmentedWidth + j2 + augmentedWidth + 1);
      }
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
  glBufferData(
    GL_ARRAY_BUFFER, sizeof(VertexNoColor) * _v.size(), &_v[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexNoColor), (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(VertexNoColor),
                        (void*)offsetof(VertexNoColor, color));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(VertexNoColor),
                        (void*)offsetof(VertexNoColor, normal));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesEbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(_indices[0]) * _indices.size(),
               &_indices[0],
               GL_STATIC_DRAW);

  glBindVertexArray(0);
}

