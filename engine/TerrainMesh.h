#ifndef TERRAIN_MESH_H
#define TERRAIN_MESH_H

#include "ModelMesh.h"

struct VertexColor
{
  glm::vec3 p;
  glm::vec3 normal;
  glm::vec3 color;
};

class TerrainMesh
{
public:
  TerrainMesh();
  ~TerrainMesh();
  void render();
  void initTerrain(float bottomLeftX,
                   float bottomLeftY,
                   float topRightX,
                   float topRightY,
                   int divisions);
  void deinit();

private:
  std::vector<VertexColor> _v;
  std::vector<unsigned int> _indices;
  GLuint _vao;
  GLuint _vertexVbo;
  GLuint _indicesEbo;
};

#endif
