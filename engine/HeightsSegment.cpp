#include "HeightsSegment.h"

HeightsSegment::HeightsSegment(Shader& colorShader,
                               Terrain* terrain,
                               glm::vec2 bottomLeft,
                               glm::vec2 topRight) :
  TerrainMeshSegment(colorShader, terrain, bottomLeft, topRight, 4.0f)
{
}

SegmentDimensions HeightsSegment::initVertices()
{
  unsigned int divisionsX;
  unsigned int divisionsY;
  unsigned int latticeWidth;
  SegmentDimensions sd;
  _terrain->getSegmentVertices(_bottomLeft, _topRight, _v, &sd);
  for (auto& v : _v) {
    v.color = glm::vec4(31, 188, 240, 150) / 255.0f;
  }
  return sd;
}

std::shared_ptr<HeightsSegment> makeHeightsSegment(Shader& colorShader,
                                                   Terrain* terrain,
                                                   glm::vec2 bottomLeft,
                                                   glm::vec2 topRight)
{
  auto hs = std::make_shared<HeightsSegment>(
    colorShader, terrain, bottomLeft, topRight);
  hs->init();
  return hs;
}
