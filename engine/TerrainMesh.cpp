#include "TerrainMesh.h"
#include "../globals.h"
#include <iostream>

void TerrainMesh::render()
{
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _v.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void TerrainMesh::init(float bottomLeftX,
                       float bottomLeftY,
                       float topRightX,
                       float topRightY,
                       int divisions,
                       float xyScale,
                       float zScale)
{
  _v.reserve((divisions + 1) * 2 * divisions);
  _width = topRightX - bottomLeftX;
  _height = topRightY - bottomLeftY;
  _xStep = (topRightX - bottomLeftX) / divisions;
  _yStep = (topRightY - bottomLeftY) / divisions;
  _xyScale = xyScale;
  _zScale = zScale;
  int width = divisions + 1;

  float min = 0.0f;
  float max = 0.0f;
  calculateHeights(width, bottomLeftX, bottomLeftY, min, max);
  auto augmentedWidth = divisions + 1 + (divisions + 1 - 2);
  _latticeAugmentedWidth = augmentedWidth;
  _latticeWidth = width;
  _latticeHeight = width;
  calculateNormals(width, _latticeAugmentedWidth);
  calculateColors(min, max, width, augmentedWidth);
  calculateIndices(divisions, divisions, _latticeAugmentedWidth);

  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(
    GL_ARRAY_BUFFER, sizeof(VertexColor) * _v.size(), &_v[0], GL_DYNAMIC_DRAW);
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

void TerrainMesh::calculateIndices(int divisionsX,
                                   int divisionsY,
                                   unsigned int latticeWidth)
{
  _indices.reserve(divisionsX * divisionsY * 2 * 3);
  for (int i = 0; i < divisionsX; ++i) {
    for (int j = 0; j < divisionsY; ++j) {
      auto j2 = j * 2;
      if (((i % 2) + j) % 2 == 0) {
        _indices.push_back(i * latticeWidth + j2);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth + 1);

        _indices.push_back(i * latticeWidth + j2 + 1);
        _indices.push_back(i * latticeWidth + j2);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth + 1);
      } else {
        _indices.push_back(i * latticeWidth + j2);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth);
        _indices.push_back(i * latticeWidth + j2 + 1);

        _indices.push_back(i * latticeWidth + j2 + 1);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth);
        _indices.push_back(i * latticeWidth + j2 + latticeWidth + 1);
      }
    }
  }
}

void TerrainMesh::calculateNormals(int width, unsigned int latticeWidth)
{
  for (int i = 0; i < width - 1; ++i) {
    for (unsigned int j = 0; j < latticeWidth; ++j) {
      glm::vec3 p0(0);
      glm::vec3 p1(0);
      glm::vec3 p2(0);
      auto rectangleTypeNum = ((i % 2) * 2 + j) % 4;
      if (rectangleTypeNum == 0) {
        p1 = _v.at(latticeWidth * i + j + 1 + latticeWidth).p;
        p2 = _v.at(latticeWidth * i + j).p;
        p0 = _v.at(latticeWidth * i + j + latticeWidth).p;
      } else if (rectangleTypeNum == 1) {
        p1 = _v.at(latticeWidth * i + j - 1).p;
        p2 = _v.at(latticeWidth * i + j + latticeWidth).p;
        p0 = _v.at(latticeWidth * i + j).p;
      } else if (rectangleTypeNum == 2) {
        p1 = _v.at(latticeWidth * i + j + latticeWidth).p;
        p2 = _v.at(latticeWidth * i + j + 1).p;
        p0 = _v.at(latticeWidth * i + j).p;
      } else if (rectangleTypeNum == 3) {
        p1 = _v.at(latticeWidth * i + j).p;
        p2 = _v.at(latticeWidth * i + j - 1 + latticeWidth).p;
        p0 = _v.at(latticeWidth * i + j + latticeWidth).p;
      }

      _v[latticeWidth * i + j].normal = glm::cross(p1 - p0, p2 - p0);
    }
  }
}

void TerrainMesh::getSegmentVertices(glm::vec2 bottomLeft,
                                     glm::vec2 topRight,
                                     std::vector<VertexColor>& v,
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

  float startI = _latticeHeight * bottomLeft.x / (_width * _xyScale);
  float startJ = _latticeAugmentedWidth * bottomLeft.y / (_height * _xyScale);
  int c = 0;
  for (unsigned int i = startI; i < startI + divisionsX; ++i) {
    c = 0;
    for (unsigned int j = startJ; j < startJ + divisionsY * 2; j += 2) {
      ++c;
      v.push_back(_v.at(_latticeAugmentedWidth * i + j));
    }
  }
  std::cout << "v.size()= " << v.size() << std::endl;
  std::cout << "vert divisionsX= " << divisionsX << std::endl;
  std::cout << "vert divisionsY= " << divisionsY << std::endl;
  std::cout << "c= " << c << std::endl;
  std::cout << std::endl;
}

float TerrainMesh::halfWidth() const
{
  return _width * _xyScale / 2;
}

float TerrainMesh::halfHeight() const
{
  return _height * _xyScale / 2;
}
