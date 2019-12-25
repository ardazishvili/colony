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

protected:
  SegmentDimensions initVertices() override;
};

std::shared_ptr<ObstaclesSegment> makeObstaclesSegment(Shader& colorShader,
                                                       Terrain* terrain,
                                                       glm::vec2 bottomLeft,
                                                       glm::vec2 topRight);

#endif
