#ifndef TERRAIN_MESH_SEGMENT_H
#define TERRAIN_MESH_SEGMENT_H

#include "Terrain.h"

class TerrainMeshSegment : public Mesh
{
public:
  TerrainMeshSegment(Shader& colorShader,
                     Terrain* terrain,
                     glm::vec2 bottomLeft,
                     glm::vec2 topRight);
  void render();

private:
  void calculateIndices(int divisionsX,
                        int divisionsY,
                        unsigned int latticeWidth);

  std::vector<VertexColor> _v;
  std::vector<unsigned int> _i;
  Shader& _colorShader;
  Terrain* _terrain;
  glm::vec2 _bottomLeft;
  glm::vec2 _topRight;
};

#endif
