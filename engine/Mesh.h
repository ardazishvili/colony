#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Animation.h"
#include "Texture.h"
#include "Vertex.h"
#define INVALID_MATERIAL 0xFFFFFFFF

using namespace std;

enum class TexturePackType
{
  PreBuild,
  Initial,
  OnSelection,
  UnderFire,
  Destroyed
};

using Textures = std::vector<std::shared_ptr<Texture>>;
class Meshes
{
public:
  Meshes();
  ~Meshes();

  struct MeshMetadata
  {
    MeshMetadata()
    {
      numIndices = 0;
      baseVertex = 0;
      baseIndex = 0;
      materialIndex = INVALID_MATERIAL;
    }

    unsigned int numIndices;
    unsigned int baseVertex;
    unsigned int baseIndex;
    unsigned int materialIndex;
    std::string name;
  };

  void render();
  bool initModel(const aiScene* pScene, const string& Filename);
  void loadTexture(const std::string& filename, TexturePackType type);
  void setActiveTexturesPack(TexturePackType type);
  void animate(Shader& shader, Animation::Type type, float percent);

private:
  void initMesh(unsigned int MeshIndex, const aiMesh* paiMesh);
  void loadBones(unsigned int MeshIndex, const aiMesh* pMesh);
  bool initMaterials(const aiScene* pScene, const string& Filename);
  void deinit();

  GLuint _vao;
  GLuint _vertexVbo;
  GLuint _indicesEbo;
  BoneMapping _boneMapping;
  std::vector<MeshMetadata> _meshesData;
  std::vector<Vertex> _vertices;
  std::vector<unsigned int> _indices;
  unsigned int _numBones;
  BonesData _bonesData;
  Animation _animation;
  bool _hasAnimation;

  Textures _initialTextures;
  Textures _onSelectionTextures;
  Textures _preBuildTextures;
  Textures _underFireTextures;
  Textures _destroyedTextures;
  TexturePackType _texturesType{ TexturePackType::Initial };
};

#endif
