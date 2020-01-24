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
  _terrain->getSegmentObstaclesMap(_bottomLeft, _topRight, _o, &_sd);
  _terrain->getSegmentVertices(_bottomLeft, _topRight, _v, &_sd);
  for (unsigned int i = 0; i < _v.size(); ++i) {
    if (_o.at(i)) {
      _v.at(i).color = glm::vec4(255, 0, 0, 255) / 255.0f;
    } else {
      _v.at(i).color = glm::vec4(0, 0, 255, 255) / 255.0f;
    }
    _v.at(i).p.z = 0.0f;
  }
  return _sd;
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

const std::vector<VertexColor>& ObstaclesSegment::vertices() const
{
  return _v;
}

const std::vector<bool>& ObstaclesSegment::obstacles() const
{
  return _o;
}

SegmentDimensions ObstaclesSegment::dimensions() const
{
  return _sd;
}
