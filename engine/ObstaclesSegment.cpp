#include "ObstaclesSegment.h"

ObstaclesSegment::ObstaclesSegment(Shader& colorShader,
                                   Terrain* terrain,
                                   glm::vec2 bottomLeft,
                                   glm::vec2 topRight) :
  TerrainMeshSegment(colorShader, terrain, bottomLeft, topRight, 8.0f)
{
}

SegmentDimensions ObstaclesSegment::initVertices()
{
  unsigned int divisionsX;
  unsigned int divisionsY;
  unsigned int latticeWidth;
  std::vector<bool> obstaclesMap;
  _terrain->getSegmentObstaclesMap(
    _bottomLeft, _topRight, obstaclesMap, divisionsX, divisionsY, latticeWidth);
  _terrain->getSegmentVertices(
    _bottomLeft, _topRight, _v, divisionsX, divisionsY, latticeWidth);
  for (unsigned int i = 0; i < _v.size(); ++i) {
    if (obstaclesMap.at(i)) {
      _v.at(i).color = glm::vec4(255, 0, 0, 255) / 255.0f;
    } else {
      _v.at(i).color = glm::vec4(0, 0, 255, 255) / 255.0f;
    }
    _v.at(i).p.z = 0.0f;
  }
  return { divisionsX, divisionsY, latticeWidth };
}

std::shared_ptr<ObstaclesSegment> makeObstaclesSegment(Shader& colorShader,
                                                       Terrain* terrain,
                                                       glm::vec2 bottomLeft,
                                                       glm::vec2 topRight)
{

  auto hs = std::make_shared<ObstaclesSegment>(
    colorShader, terrain, bottomLeft, topRight);
  hs->init();
  return hs;
}
