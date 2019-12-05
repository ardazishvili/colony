#ifndef SURFACE_MESH_H
#define SURFACE_MESH_H

#include "Mesh.h"

class SurfaceMesh
{
public:
  SurfaceMesh();
  ~SurfaceMesh();
  void render();
  void initSurface(
    float bottomLeftX,
    float bottomLeftY,
    float topRightX,
    float topRightY,
    int divisions,
    std::string texturePath = "/home/roman/repos/opengl/assets/grey.png");
  void loadTexture(const std::string& filename, TexturePackType type);
  void deinit();

private:
  std::vector<Meshes::MeshMetadata> _meshesData;
  std::vector<Vertex> _vertices;
  std::vector<unsigned int> _indices;
  Textures _initialTextures;
  GLuint _vao;
  GLuint _vertexVbo;
  GLuint _indicesEbo;
};

#endif
