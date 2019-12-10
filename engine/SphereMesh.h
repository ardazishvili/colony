#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include "TerrainMesh.h"

class SphereMesh
{
public:
  SphereMesh();
  ~SphereMesh();
  void init(float r, unsigned int divisions);
  void render();

private:
  void deinit();

  std::vector<VertexColor> _v;
  std::vector<unsigned int> _indices;
  GLuint _vao;
  GLuint _vertexVbo;
  GLuint _indicesEbo;
};

#endif
