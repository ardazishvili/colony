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
  _latticeWidth = augmentedWidth;
  _latticeHeight = width;
  calculateNormals(width, _latticeWidth);
  calculateColors(min, max, width, augmentedWidth);
  calculateIndices(divisions, divisions, _latticeWidth);

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
                                     int& divisionsX,
                                     int& divisionsY,
                                     unsigned int& latticeWidth)
{
  std::cout << "bottomLeft.x= " << bottomLeft.x << std::endl;
  std::cout << "bottomLeft.y= " << bottomLeft.y << std::endl;
  std::cout << "topRight.x= " << topRight.x << std::endl;
  std::cout << "topRight.y= " << topRight.y << std::endl;

  divisionsX = (topRight.x - bottomLeft.x) / (_xStep * _xyScale);
  divisionsY = (topRight.y - bottomLeft.y) / (_yStep * _xyScale);

  auto factor = (topRight.y - bottomLeft.y) / (_height * _xyScale);
  /* std::cout << "_height= " << _height << std::endl; */
  /* std::cout << "factor= " << factor << std::endl; */
  /* latticeWidth = factor * _latticeWidth; */
  latticeWidth = divisionsY + 1;

  bottomLeft.x += _width * _xyScale / 2;
  topRight.x += _width * _xyScale / 2;
  bottomLeft.y += _height * _xyScale / 2;
  topRight.y += _height * _xyScale / 2;

  float startI = _latticeHeight * bottomLeft.x / (_width * _xyScale);
  float startJ = _latticeWidth * bottomLeft.y / (_height * _xyScale);
  std::cout << "startI= " << startI << std::endl;
  std::cout << "startJ= " << startJ << std::endl;
  for (unsigned int i = startI; i < startI + divisionsX; ++i) {
    for (unsigned int j = startJ; j < startJ + divisionsY * 2; j += 2) {
      /* std::cout << "i= " << i << std::endl; */
      /* std::cout << "j= " << j << std::endl; */
      auto vertex = _v.at(_latticeWidth * i + j);
      vertex.p.x -= _width * _xyScale / 2;
      vertex.p.y -= _height * _xyScale / 2;
      vertex.p.z += 5.0f;
      vertex.color = glm::vec4(31, 188, 240, 100) / 255.0f;
      v.push_back(vertex);
    }
  }
}
