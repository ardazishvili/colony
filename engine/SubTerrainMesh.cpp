#include <iostream>
#include <string>

#include "../math/Noise.h"
#include "SubTerrainMesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

const glm::vec4 SubTerrainMesh::SELECTION_COLOR{ 0.0f, 0.0f, 1.0f, 0.3f };
const glm::vec4 SubTerrainMesh::DESELECTION_COLOR{ 0.0f, 0.0f, 1.0f, 0.0f };

std::shared_ptr<LivingArea> SubTerrainMesh::addLivingArea(CircularRegion region,
                                                          glm::vec4 rgba)
{
  RectangleRegion rect = {
    region.x - region.r, region.y - region.r, 2 * region.r, 2 * region.r
  };
  rect.x += _width;
  rect.y += _height;
  auto x = region.x + _width;
  auto y = region.y + _height;
  auto r = region.r;

  auto i = ::floor(rect.x / _xStep / _xyScale);
  auto j = ::floor(rect.y / _yStep);
  signed int xWidth = rect.width / _xStep / _xyScale;
  signed int yWidth = rect.height / _yStep;
  auto livingArea = std::make_shared<LivingArea>();
  for (unsigned int k = i; k <= i + xWidth; ++k) {
    unsigned int index = 0;
    unsigned int stride = 0;
    auto indexIsSet = false;
    for (unsigned int n = j; n < j + yWidth; ++n) {
      auto c = _v.at(_latticeWidth * k + n);

      if (::sqrt(::pow(x - c.p.x, 2) + ::pow(y - c.p.y, 2)) < r) {
        if (!indexIsSet) {
          index = _latticeWidth * k + n;
          indexIsSet = true;
        }
        _v.at(_latticeWidth * k + n).color = rgba;

        ++stride;
      }
    }
    livingArea->cells.push_back(std::make_pair(index, stride));
  }
  reloadLivingArea(livingArea);
  _livingAreas.push_back(livingArea);
  return livingArea;
}

void SubTerrainMesh::reloadLivingArea(std::shared_ptr<LivingArea> area)
{
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  for (auto& cell : area->cells) {
    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(VertexColor) * (cell.first),
                    sizeof(VertexColor) * cell.second,
                    &_v[cell.first]);
  }
}

void SubTerrainMesh::updateLivingArea(std::shared_ptr<LivingArea> area)
{
  for (auto plant : area->plants) {
    plant.x += _width;
    plant.y += _height;
    for (auto& cell : area->cells) {
      for (unsigned int i = cell.first; i < cell.first + cell.second; ++i) {
        auto cellX = _v.at(i).p.x;
        auto cellY = _v.at(i).p.y;
        float d = ::sqrt(::pow(cellX - plant.x, 2) + ::pow(cellY - plant.y, 2));
        d /= 2.0;
        double g = _v.at(i).color.y;
        auto newColor = glm::lerp(g, 1.0, ::pow(1.0f - d / 3, 20) / 30);
        _v.at(i).color.y = newColor;
      }
    }
  }
  reloadLivingArea(area);
}

void SubTerrainMesh::selectSubTerrainRegion(RectangleRegion region,
                                            glm::vec4 rgba)
{
  _lastSelected = region;

  region.x += _width;
  region.y += _height;

  auto i = ::floor(region.x / _xStep / _xyScale);
  auto j = ::floor(region.y / _yStep);
  signed int xWidth = region.width / _xStep / _xyScale;
  signed int yWidth = region.height / _yStep;
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  unsigned int leftXBound = std::min(i, i + xWidth);
  unsigned int rightXBound = std::max(i, i + xWidth);
  unsigned int leftYBound = std::min(j, j + yWidth);
  unsigned int rightYBound = std::max(j, j + yWidth);
  for (unsigned int k = leftXBound; k < rightXBound; ++k) {
    auto index = _latticeWidth * k + leftYBound;
    for (unsigned int n = leftYBound; n < rightYBound; ++n) {
      _v.at(_latticeWidth * k + n).color = rgba;
    }
    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(VertexColor) * (index),
                    sizeof(VertexColor) * ::abs(yWidth),
                    &_v[index]);
  }
}

void SubTerrainMesh::deselect()
{
  selectSubTerrainRegion(_lastSelected, DESELECTION_COLOR);
}

void SubTerrainMesh::calculateHeights(unsigned int width,
                                      float bottomLeftX,
                                      float bottomLeftY,
                                      float& min,
                                      float& max)
{
  static float frequency = 0.077;
  static float frequencyFactor = 3.0;
  static float amplitudeFactor = 0.366;
  auto noise = Noise(777);
  std::vector<float> plainZ;
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
      vertex.p.z = nv + 0.03f;
      vertex.normal = glm::vec3(0.0f);
      vertex.color = glm::vec4(0.0f, 0.0f, 1.0f, 0.0);

      _v.push_back(vertex);
      if (j != 0 && j != (width - 1)) {
        _v.push_back(vertex);
      }
    }
  }
}

void SubTerrainMesh::calculateColors(float min,
                                     float max,
                                     unsigned int width,
                                     unsigned int augmentedWidth)
{
}
