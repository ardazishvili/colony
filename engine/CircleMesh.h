#ifndef CIRCLE_MESH_H
#define CIRCLE_MESH_H

#include "TerrainMesh.h"

class CircleMesh
{
public:
  CircleMesh();
  ~CircleMesh();
  void init(float radius, unsigned int divisions);
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
