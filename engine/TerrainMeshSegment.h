#ifndef TERRAIN_MESH_SEGMENT_H
#define TERRAIN_MESH_SEGMENT_H

#include "Terrain.h"

struct SegmentDimensions
{
  unsigned int divisionsX;
  unsigned int divisionsY;
  unsigned int latticeWidth;
  float xStep;
  float yStep;
};

class TerrainMeshSegment : public Mesh
{
public:
  TerrainMeshSegment(Shader& colorShader,
                     Terrain* terrain,
                     glm::vec2 bottomLeft,
                     glm::vec2 topRight,
                     float zOffset);
  void init();
  void render();
  virtual SegmentDimensions initVertices() = 0;

protected:
  void calculateIndices(SegmentDimensions sd);

  std::vector<VertexColor> _v;
  std::vector<unsigned int> _i;
  Shader& _colorShader;
  Terrain* _terrain;
  glm::vec2 _bottomLeft;
  glm::vec2 _topRight;
  float _zOffset;
};

#endif
