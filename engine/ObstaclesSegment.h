#ifndef OBSTACLES_SEGMENT_H
#define OBSTACLES_SEGMENT_H

#include "TerrainMeshSegment.h"

class ObstaclesSegment : public TerrainMeshSegment
{
public:
  ObstaclesSegment(Shader& colorShader,
                   Terrain* terrain,
                   glm::vec2 bottomLeft,
                   glm::vec2 topRight);
  const std::vector<VertexColor>& vertices() const;
  const std::vector<bool>& obstacles() const;
  SegmentDimensions dimensions() const;

protected:
  SegmentDimensions initVertices() override;
  std::vector<bool> _o;
  SegmentDimensions _sd;
};

std::shared_ptr<ObstaclesSegment> makeObstaclesSegment(Shader& colorShader,
                                                       Terrain* terrain,
                                                       glm::vec2 bottomLeft,
                                                       glm::vec2 topRight);

#endif
