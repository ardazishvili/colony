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
  float getZ(float x, float y) const;

private:
  std::vector<VertexColor> _v;
  std::vector<unsigned int> _indices;
  unsigned int _width;
  unsigned int _height;
  float _xStep;
  float _yStep;
  GLuint _vao;
  GLuint _vertexVbo;
  GLuint _indicesEbo;
};

#endif
