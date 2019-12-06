#ifndef SURFACE_MESH_H
#define SURFACE_MESH_H

#include "Mesh.h"

struct VertexNoColor
{
  glm::vec3 p;
  glm::vec3 normal;
  glm::vec3 color;
};

class SurfaceMesh
{
public:
  SurfaceMesh();
  ~SurfaceMesh();
  void render();
  void initSurface(float bottomLeftX,
                   float bottomLeftY,
                   float topRightX,
                   float topRightY,
                   int divisions);
  void deinit();

private:
  std::vector<Meshes::MeshMetadata> _meshesData;
  std::vector<VertexNoColor> _v;
  std::vector<unsigned int> _indices;
  GLuint _vao;
  GLuint _vertexVbo;
  GLuint _indicesEbo;
};

#endif
