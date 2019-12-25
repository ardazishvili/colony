#ifndef HEIGHTS_SEGMENT_H
#define HEIGHTS_SEGMENT_H

#include "TerrainMeshSegment.h"

class HeightsSegment : public TerrainMeshSegment
{
public:
  HeightsSegment(Shader& colorShader,
                 Terrain* terrain,
                 glm::vec2 bottomLeft,
                 glm::vec2 topRight);

protected:
  SegmentDimensions initVertices() override;
};

std::shared_ptr<HeightsSegment> makeHeightsSegment(Shader& colorShader,
                                                   Terrain* terrain,
                                                   glm::vec2 bottomLeft,
                                                   glm::vec2 topRight);

#endif
