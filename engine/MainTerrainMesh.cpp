#include <algorithm>
#include <iostream>
#include <map>
#include <string>

#include "../imgui/imgui.h"

#include "../math/Noise.h"
#include "MainTerrainMesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

struct RgbColor
{
  float r;
  float g;
  float b;
};

using HeightPart = float;
std::map<HeightPart, RgbColor> colorMapping = {
  { 0.0f, { 113.0f / 255, 128.0f / 255, 143.0f / 255 } },
  { 0.5f, { 237.0f / 255, 227.0f / 255, 143.0f / 255 } },
  { 1.0f, { 242.0f / 255, 127.0f / 255, 115.0f / 255 } }
};

void MainTerrainMesh::calculateHeights(unsigned int width,
                                       float bottomLeftX,
                                       float bottomLeftY,
                                       float& min,
                                       float& max)
{
  static float frequency = 0.3;
  static float frequencyFactor = 2.0;
  static float amplitudeFactor = 0.6;
  static float frequency_plain = 0.077;
  static float frequencyFactor_plain = 3.0;
  static float amplitudeFactor_plain = 0.366;
  auto noise = Noise(777);
  std::vector<float> plainZ;
  float x, y;
  for (unsigned int i = 0; i < width; ++i) {
    for (unsigned int j = 0; j < width; ++j) {
      auto dummy = glm::vec2();
      x = bottomLeftX + static_cast<float>(i) * _xStep;
      y = bottomLeftY + static_cast<float>(j) * _yStep;
      auto nv_plain = noise.fractal(glm::vec2(x, y),
                                    dummy,
                                    frequency_plain,
                                    frequencyFactor_plain,
                                    amplitudeFactor_plain,
                                    5);
      plainZ.push_back(nv_plain);
    }
  }
  for (unsigned int i = 0; i < width; ++i) {
    for (unsigned int j = 0; j < width; ++j) {
      VertexColor vertex;
      vertex.p.x = bottomLeftX + static_cast<float>(i) * _xStep;
      vertex.p.y = bottomLeftY + static_cast<float>(j) * _yStep;
      glm::vec2 derivs;
      auto nv = noise.fractal(glm::vec2(vertex.p.x, vertex.p.y),
                              derivs,
                              frequency,
                              frequencyFactor,
                              amplitudeFactor,
                              5);
      vertex.p.x *= _xyScale;
      vertex.p.y *= _xyScale;
      auto nonPlain = nv * _zScale;
      auto plain = plainZ.at(i * width + j);
      if (nonPlain > plain) {
        vertex.p.z = nonPlain;
        _obstaclesMap.push_back(true);
      } else {
        vertex.p.z = plain;
        _obstaclesMap.push_back(false);
      }
      min = std::min(min, vertex.p.z);
      max = std::max(max, vertex.p.z);
      vertex.normal = glm::vec3(0.0f);

      _v.push_back(vertex);
      if (j != 0 && j != (width - 1)) {
        _v.push_back(vertex);
      }
    }
  }
}

void MainTerrainMesh::calculateColors(float min,
                                      float max,
                                      unsigned int width,
                                      unsigned int augmentedWidth)
{
  auto amplitude = max - min;
  for (unsigned int i = 0; i < width; ++i) {
    for (unsigned int j = 0; j < augmentedWidth; ++j) {
      RgbColor a, b;
      auto h = (_v[augmentedWidth * i + j].p.z - min) / amplitude;
      if (h <= amplitude * 0.2) {
        a = colorMapping[0.0f];
        b = colorMapping[0.5f];
        h *= 2;
      } else {
        a = colorMapping[0.5f];
        b = colorMapping[1.0f];
        h = (h - 0.5) * 2;
      }
      _v[augmentedWidth * i + j].color.x = glm::lerp(a.r, b.r, h);
      _v[augmentedWidth * i + j].color.y = glm::lerp(a.g, b.g, h);
      _v[augmentedWidth * i + j].color.z = glm::lerp(a.b, b.b, h);
      _v[augmentedWidth * i + j].color.w = 1.0;
    }
  }
}

float MainTerrainMesh::getZ(float x, float y) const
{
  x += _width / 2;
  y += _height / 2;
  auto i = ::floor(x / _xStep / _xyScale);
  auto j = ::floor(y / _yStep / _xyScale);
  auto mappedJ = (j == 0) ? 0 : 2 * j - 1;
  return _v.at(i * _latticeAugmentedWidth + mappedJ).p.z;
}

glm::vec3 MainTerrainMesh::getRgbColor(float x, float y) const
{
  x += _width / 2;
  y += _height / 2;
  auto i = ::floor(x / _xStep / _xyScale);
  auto j = ::floor(y / _yStep / _xyScale);
  auto mappedJ = (j == 0) ? 0 : 2 * j - 1;
  auto c = _v.at(i * _latticeAugmentedWidth + mappedJ).color;
  return glm::vec3(c.x, c.y, c.z);
}

void MainTerrainMesh::getSegmentObstaclesMap(glm::vec2 bottomLeft,
                                             glm::vec2 topRight,
                                             std::vector<bool>& m,
                                             unsigned int& divisionsX,
                                             unsigned int& divisionsY,
                                             unsigned int& latticeWidth)
{
  divisionsX = (topRight.x - bottomLeft.x) / (_xStep * _xyScale);
  divisionsY = (topRight.y - bottomLeft.y) / (_yStep * _xyScale);
  latticeWidth = divisionsY + 1;

  bottomLeft.x += _width * _xyScale / 2;
  topRight.x += _width * _xyScale / 2;
  bottomLeft.y += _height * _xyScale / 2;
  topRight.y += _height * _xyScale / 2;

  unsigned int startI = _latticeHeight * bottomLeft.x / (_width * _xyScale);
  unsigned int startJ = _latticeWidth * bottomLeft.y / (_height * _xyScale);
  for (unsigned int i = startI; i < startI + divisionsX + 1; ++i) {
    for (unsigned int j = startJ; j < startJ + divisionsY + 1; ++j) {
      m.push_back(_obstaclesMap.at(_latticeWidth * i + j));
    }
  }
}
