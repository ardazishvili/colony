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
  for (unsigned int i = 0; i < divisionsY; ++i) {
    for (unsigned int j = 0; j < divisionsX; ++j) {
      std::cout << obstaclesMap.at(i * divisionsX + j);
    }
    std::cout << std::endl;
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
