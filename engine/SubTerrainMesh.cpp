#include <iostream>
#include <string>

#include "../globals.h"
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
  auto x = region.x;
  auto y = region.y;
  auto r = region.r;

  auto i = ::floor(rect.x / _xStep) + _latticeWidth / 2;
  auto j = ::floor(rect.y / _yStep) + _latticeAugmentedWidth / 2;
  signed int xWidth = rect.width / _xStep;
  signed int yWidth = rect.height / _yStep;
  auto livingArea = std::make_shared<LivingArea>();
  auto center = glm::vec2(x, y);
  for (unsigned int k = i; k <= i + xWidth; ++k) {
    unsigned int index = 0;
    unsigned int stride = 0;
    auto indexIsSet = false;
    for (unsigned int n = j; n < j + yWidth; ++n) {
      auto m = k * _latticeAugmentedWidth + n;
      auto c = _v.at(m);

      auto point = glm::vec2(c.p.x, c.p.y);
      if (glm::distance(point, center) < r) {
        if (!indexIsSet) {
          index = m;
          indexIsSet = true;
        }
        _v.at(m).color = rgba;

        ++stride;
      }
    }
    livingArea->cells.push_back(std::make_pair(index, stride));
    livingArea->region = region;
    livingArea->initRgba = rgba;
  }
  reloadLivingArea(livingArea);
  _livingAreas.push_back(livingArea);
  return livingArea;
}

void SubTerrainMesh::growLivingArea(std::shared_ptr<LivingArea> area,
                                    float radius)
{
  auto prevRadius = area->region.r;
  area->region.r = radius;
  auto region = area->region;
  RectangleRegion rect = {
    region.x - region.r, region.y - region.r, 2 * region.r, 2 * region.r
  };
  auto x = region.x;
  auto y = region.y;
  auto r = region.r;

  auto i = ::floor(rect.x / _xStep) + _latticeWidth / 2;
  auto j = ::floor(rect.y / _yStep) + _latticeAugmentedWidth / 2;
  signed int xWidth = rect.width / _xStep;
  signed int yWidth = rect.height / _yStep;
  auto cells = Cells();
  auto center = glm::vec2(x, y);
  for (unsigned int k = i; k <= i + xWidth; ++k) {
    unsigned int index = 0;
    unsigned int stride = 0;
    auto indexIsSet = false;
    for (unsigned int n = j; n < j + yWidth; ++n) {
      auto m = k * _latticeAugmentedWidth + n;
      auto c = _v.at(m);

      auto point = glm::vec2(c.p.x, c.p.y);
      auto distance = glm::distance(point, center);
      if (distance < r) {
        if (!indexIsSet) {
          index = m;
          indexIsSet = true;
        }
        if (distance >= prevRadius - 0.1) {
          _v.at(m).color = area->initRgba;
        }

        ++stride;
      }
    }
    cells.push_back(std::make_pair(index, stride));
  }
  area->cells = cells;
  reloadLivingArea(area);
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
  logger.log("begin area update");
  reloadLivingArea(area);
  area->future = std::async(std::launch::async, [this, area]() {
    for (auto plant : area->plants) {
      for (auto& cell : area->cells) {
        for (unsigned int i = cell.first; i < cell.first + cell.second; ++i) {
          auto cellX = _v.at(i).p.x;
          auto cellY = _v.at(i).p.y;
          float d =
            ::sqrt(::pow(cellX - plant.x, 2) + ::pow(cellY - plant.y, 2));
          d /= 2.0;
          double g = _v.at(i).color.y;
          auto newColor = glm::lerp(g, 1.0, ::pow(1.0f - d / 3, 20) / 30);
          _v.at(i).color.y = newColor;
        }
      }
    }
  });
  logger.log("end area update");
}

void SubTerrainMesh::calculateHeights(unsigned int width,
                                      float bottomLeftX,
                                      float bottomLeftY,
                                      float& min,
                                      float& max)
{
  static float frequency = 0.077;
  static float frequencyFactor = 4.0;
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
      vertex.p.x -= _width / 2.0f;
      vertex.p.y -= _height / 2.0f;
      vertex.p.z = nv + 0.1;
      _v.push_back(vertex);
    }
  }
}

void SubTerrainMesh::calculateIndices(int divisionsX,
                                      int divisionsY,
                                      unsigned int latticeWidth)
{
  _indices.reserve(divisionsX * divisionsY * 2 * 3);
  for (int i = 0; i < divisionsX; ++i) {
    for (int j = 0; j < divisionsY; ++j) {
      _indices.push_back((i * latticeWidth) + j);
      _indices.push_back((i * latticeWidth) + j + 1);
      _indices.push_back((i * latticeWidth) + j + latticeWidth);

      _indices.push_back((i * latticeWidth) + j + 1);
      _indices.push_back((i * latticeWidth) + j + latticeWidth);
      _indices.push_back((i * latticeWidth) + j + latticeWidth + 1);
    }
  }
}

void SubTerrainMesh::calculateColors(float min,
                                     float max,
                                     unsigned int width,
                                     unsigned int augmentedWidth)
{
}
