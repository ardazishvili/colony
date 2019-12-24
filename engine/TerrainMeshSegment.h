#ifndef TERRAIN_MESH_SEGMENT_H
#define TERRAIN_MESH_SEGMENT_H

#include "Terrain.h"

class TerrainMeshSegment : public Mesh
{
public:
  TerrainMeshSegment(Shader& colorShader, Terrain* terrain);
  void addData(glm::vec2 bottomLeft, glm::vec2 topRight);
  void clear();
  void render();
  bool settedUp() const;

private:
  void calculateIndices(int divisionsX,
                        int divisionsY,
                        unsigned int latticeWidth);

  Shader& _colorShader;
  std::vector<VertexColor> _v;
  std::vector<unsigned int> _i;
  Terrain* _terrain;
};

#endif
