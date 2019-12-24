#include "TerrainMeshSegment.h"
#include "../globals.h"

TerrainMeshSegment::TerrainMeshSegment(Shader& colorShader,
                                       Terrain* terrain,
                                       glm::vec2 bottomLeft,
                                       glm::vec2 topRight) :
  _colorShader(colorShader),
  _terrain(terrain)
{

  /* std::cout << "bottomLeft.x= " << bottomLeft.x << std::endl; */
  /* std::cout << "bottomLeft.y= " << bottomLeft.y << std::endl; */
  /* std::cout << "topRight.x= " << topRight.x << std::endl; */
  /* std::cout << "topRight.y= " << topRight.y << std::endl; */
  int divisionsX;
  int divisionsY;
  unsigned int latticeWidth;
  _terrain->getSegmentVertices(
    bottomLeft, topRight, _v, divisionsX, divisionsY, latticeWidth);
  std::cout << "divisionsX= " << divisionsX << std::endl;
  std::cout << "divisionsY= " << divisionsY << std::endl;
  std::cout << "latticeWidth= " << latticeWidth << std::endl;
  calculateIndices(divisionsX, divisionsY, latticeWidth);
  for (auto v : _v) {
    std::cout << " v.p.x= " << v.p.x;
    std::cout << " v.p.y= " << v.p.y;
    std::cout << " v.p.z= " << v.p.z;
    std::cout << std::endl;
    std::cout << std::endl;
  }
  for (auto i : _i) {
    std::cout << "i= " << i << std::endl;
  }

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
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER, sizeof(_i[0]) * _i.size(), &_i[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}

// TODO copypaste from TerrainMesh
void TerrainMeshSegment::calculateIndices(int divisionsX,
                                          int divisionsY,
                                          unsigned int latticeWidth)
{
  _i.reserve(divisionsX * divisionsY * 2 * 3);
  for (int i = 0; i < divisionsX; ++i) {
    for (int j = 0; j < divisionsY; ++j) {
      _i.push_back((i * latticeWidth) + j);
      _i.push_back((i * latticeWidth) + j + 1);
      _i.push_back((i * latticeWidth) + j + latticeWidth);

      _i.push_back((i * latticeWidth) + j + 1);
      _i.push_back((i * latticeWidth) + j + latticeWidth);
      _i.push_back((i * latticeWidth) + j + latticeWidth + 1);
    }
  }
}

void TerrainMeshSegment::render()
{
  _colorShader.use();
  _colorShader.configure();
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  auto model = glm::mat4(1.0f);
  /* model = glm::translate(model, _offset * _xyScale); */
  _colorShader.setTransformation("model", glm::value_ptr(model));
  _colorShader.setBool("animated", false);

  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _i.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
}
