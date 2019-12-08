#ifndef PLAIN_MESH_H
#define PLAIN_MESH_H

#include "ModelMesh.h"

class PlainMesh
{
public:
  PlainMesh();
  ~PlainMesh();
  void render();
  void initSurface(
    float bottomLeftX,
    float bottomLeftY,
    float topRightX,
    float topRightY,
    int divisions,
    std::string texturePath = "/home/roman/repos/colony/assets/grey.png");
  void loadTexture(const std::string& filename, TexturePackType type);

private:
  void deinit();

  std::vector<ModelMesh::MeshMetadata> _meshesData;
  Textures _initialTextures;
  std::vector<Vertex> _vertices;
  std::vector<unsigned int> _indices;
  GLuint _vao;
  GLuint _vertexVbo;
  GLuint _indicesEbo;
};

#endif
