#include "TerrainMeshSegment.h"
#include "../globals.h"

TerrainMeshSegment::TerrainMeshSegment(Shader& colorShader,
                                       Terrain* terrain,
                                       glm::vec2 bottomLeft,
                                       glm::vec2 topRight,
                                       float zOffset) :
  _colorShader(colorShader),
  _terrain(terrain), _bottomLeft(bottomLeft), _topRight(topRight),
  _zOffset(zOffset)
{
}
void TerrainMeshSegment::init()
{
  auto sd = initVertices();
  calculateIndices(sd);

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

// TODO copypaste from PlainMesh
void TerrainMeshSegment::calculateIndices(SegmentDimensions sd)
{
  _i.reserve(sd.divisionsX * sd.divisionsY * 2 * 3);
  for (unsigned int i = 0; i < sd.divisionsX; ++i) {
    for (unsigned int j = 0; j < sd.divisionsY; ++j) {
      _i.push_back((i * sd.latticeWidth) + j);
      _i.push_back((i * sd.latticeWidth) + j + 1);
      _i.push_back((i * sd.latticeWidth) + j + sd.latticeWidth);

      _i.push_back((i * sd.latticeWidth) + j + 1);
      _i.push_back((i * sd.latticeWidth) + j + sd.latticeWidth);
      _i.push_back((i * sd.latticeWidth) + j + sd.latticeWidth + 1);
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
  model = glm::translate(model, glm::vec3(0, 0, _zOffset));
  _colorShader.setTransformation("model", glm::value_ptr(model));
  _colorShader.setBool("animated", false);

  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _i.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
}
