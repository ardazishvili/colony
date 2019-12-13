#include <iostream>
#include <string>

#include "../math/Noise.h"
#include "SubTerrainMesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

const glm::vec4 SubTerrainMesh::SELECTION_COLOR{ 0.0f, 0.0f, 1.0f, 0.3f };
const glm::vec4 SubTerrainMesh::DESELECTION_COLOR{ 0.0f, 0.0f, 1.0f, 0.0f };

/* SubTerrainMesh::SubTerrainMesh() */
/* { */
/*   _vaoSub = 0; */
/*   _vertexVboSub = 0; */
/*   _indicesEboSub = 0; */

/*   deinit(); */

/*   glGenVertexArrays(1, &_vaoSub); */
/*   glGenBuffers(1, &_vertexVboSub); */
/*   glGenBuffers(1, &_indicesEboSub); */
/* } */

/* SubTerrainMesh::~SubTerrainMesh() */
/* { */
/*   deinit(); */
/* } */

/* void SubTerrainMesh::deinit() */
/* { */
/*   if (_vertexVboSub != 0) { */
/*     glDeleteBuffers(1, &_vertexVboSub); */
/*     glDeleteBuffers(1, &_indicesEboSub); */
/*   } */

/*   if (_vaoSub != 0) { */
/*     glDeleteVertexArrays(1, &_vaoSub); */
/*     _vaoSub = 0; */
/*   } */
/* } */

void SubTerrainMesh::render()
{
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _vSub.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

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

  auto i = ::floor(rect.x / _xStepSub / _xyScale);
  auto j = ::floor(rect.y / _yStepSub);
  signed int xWidth = rect.width / _xStepSub / _xyScale;
  signed int yWidth = rect.height / _yStepSub;
  auto livingArea = std::make_shared<LivingArea>();
  for (unsigned int k = i; k <= i + xWidth; ++k) {
    unsigned int index = 0;
    unsigned int stride = 0;
    auto indexIsSet = false;
    for (unsigned int n = j; n < j + yWidth; ++n) {
      auto c = _vSub.at(_latticeWidthSub * k + n);

      if (::sqrt(::pow(x - c.p.x, 2) + ::pow(y - c.p.y, 2)) < r) {
        if (!indexIsSet) {
          index = _latticeWidthSub * k + n;
          indexIsSet = true;
        }
        _vSub.at(_latticeWidthSub * k + n).color = rgba;

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
                    &_vSub[cell.first]);
  }
}

void SubTerrainMesh::updateLivingArea(std::shared_ptr<LivingArea> area)
{
  for (auto plant : area->plants) {
    plant.x += _width;
    plant.y += _height;
    for (auto& cell : area->cells) {
      for (unsigned int i = cell.first; i < cell.first + cell.second; ++i) {
        auto cellX = _vSub.at(i).p.x;
        auto cellY = _vSub.at(i).p.y;
        float d = ::sqrt(::pow(cellX - plant.x, 2) + ::pow(cellY - plant.y, 2));
        d /= 2.0;
        double g = _vSub.at(i).color.y;
        auto newColor = glm::lerp(g, 1.0, ::pow(1.0f - d / 3, 20) / 30);
        _vSub.at(i).color.y = newColor;
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

  auto i = ::floor(region.x / _xStepSub / _xyScale);
  auto j = ::floor(region.y / _yStepSub);
  signed int xWidth = region.width / _xStepSub / _xyScale;
  signed int yWidth = region.height / _yStepSub;
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  unsigned int leftXBound = std::min(i, i + xWidth);
  unsigned int rightXBound = std::max(i, i + xWidth);
  unsigned int leftYBound = std::min(j, j + yWidth);
  unsigned int rightYBound = std::max(j, j + yWidth);
  for (unsigned int k = leftXBound; k < rightXBound; ++k) {
    auto index = _latticeWidthSub * k + leftYBound;
    for (unsigned int n = leftYBound; n < rightYBound; ++n) {
      _vSub.at(_latticeWidthSub * k + n).color = rgba;
    }
    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(VertexColor) * (index),
                    sizeof(VertexColor) * ::abs(yWidth),
                    &_vSub[index]);
  }
}

void SubTerrainMesh::deselect()
{
  selectSubTerrainRegion(_lastSelected, DESELECTION_COLOR);
}

void SubTerrainMesh::init(float bottomLeftX,
                          float bottomLeftY,
                          float topRightX,
                          float topRightY,
                          int divisions,
                          float xyScale,
                          float zScale)
{

  _width = topRightX - bottomLeftX;
  _height = topRightY - bottomLeftY;
  _xyScale = xyScale;
  _zScale = zScale;
  _vSub.reserve((divisions + 1) * 2 * divisions);
  _xStepSub = (topRightX - bottomLeftX) / divisions;
  _yStepSub = (topRightY - bottomLeftY) / divisions;

  static float frequency = 0.077;
  static float frequencyFactor = 3.0;
  static float amplitudeFactor = 0.366;
  auto noise = Noise(777);
  int width = divisions + 1;
  std::vector<float> plainZ;
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < width; ++j) {
      VertexColor vertex;
      vertex.p.x = bottomLeftX + static_cast<float>(i) * _xStepSub;
      vertex.p.y = bottomLeftY + static_cast<float>(j) * _yStepSub;
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

      _vSub.push_back(vertex);
      if (j != 0 && j != (width - 1)) {
        _vSub.push_back(vertex);
      }
    }
  }
  auto augmentedWidth = divisions + 1 + (divisions + 1 - 2);
  _latticeWidthSub = augmentedWidth;
  for (int i = 0; i < width - 1; ++i) {
    for (int j = 0; j < augmentedWidth; ++j) {
      glm::vec3 p0(0);
      glm::vec3 p1(0);
      glm::vec3 p2(0);
      auto rectangleTypeNum = ((i % 2) * 2 + j) % 4;
      if (rectangleTypeNum == 0) {
        p1 = _vSub.at(augmentedWidth * i + j + 1 + augmentedWidth).p;
        p2 = _vSub.at(augmentedWidth * i + j).p;
        p0 = _vSub.at(augmentedWidth * i + j + augmentedWidth).p;
      } else if (rectangleTypeNum == 1) {
        p1 = _vSub.at(augmentedWidth * i + j - 1).p;
        p2 = _vSub.at(augmentedWidth * i + j + augmentedWidth).p;
        p0 = _vSub.at(augmentedWidth * i + j).p;
      } else if (rectangleTypeNum == 2) {
        p1 = _vSub.at(augmentedWidth * i + j + augmentedWidth).p;
        p2 = _vSub.at(augmentedWidth * i + j + 1).p;
        p0 = _vSub.at(augmentedWidth * i + j).p;
      } else if (rectangleTypeNum == 3) {
        p1 = _vSub.at(augmentedWidth * i + j).p;
        p2 = _vSub.at(augmentedWidth * i + j - 1 + augmentedWidth).p;
        p0 = _vSub.at(augmentedWidth * i + j + augmentedWidth).p;
      }

      _vSub[augmentedWidth * i + j].normal = glm::cross(p1 - p0, p2 - p0);
    }
  }
  _indicesSub.reserve(::pow(divisions, 2) * 2 * 3);
  for (int i = 0; i < divisions; ++i) {
    for (int j = 0; j < divisions; ++j) {
      auto j2 = j * 2;
      if (((i % 2) + j) % 2 == 0) {
        _indicesSub.push_back(i * augmentedWidth + j2);
        _indicesSub.push_back(i * augmentedWidth + j2 + augmentedWidth);
        _indicesSub.push_back(i * augmentedWidth + j2 + augmentedWidth + 1);

        _indicesSub.push_back(i * augmentedWidth + j2 + 1);
        _indicesSub.push_back(i * augmentedWidth + j2);
        _indicesSub.push_back(i * augmentedWidth + j2 + augmentedWidth + 1);

      } else {
        _indicesSub.push_back(i * augmentedWidth + j2);
        _indicesSub.push_back(i * augmentedWidth + j2 + augmentedWidth);
        _indicesSub.push_back(i * augmentedWidth + j2 + 1);

        _indicesSub.push_back(i * augmentedWidth + j2 + 1);
        _indicesSub.push_back(i * augmentedWidth + j2 + augmentedWidth);
        _indicesSub.push_back(i * augmentedWidth + j2 + augmentedWidth + 1);
      }
    }
  }

  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(VertexColor) * _vSub.size(),
               &_vSub[0],
               GL_DYNAMIC_DRAW);
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
               sizeof(_indicesSub[0]) * _indicesSub.size(),
               &_indicesSub[0],
               GL_STATIC_DRAW);

  glBindVertexArray(0);
}
