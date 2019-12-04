#include "Mesh.h"
#include "../math/Noise.h"

bool Meshes::initModel(const aiScene* scene, const string& Filename)
{
  _meshesData.resize(scene->mNumMeshes);
  _initialTextures.resize(scene->mNumMaterials);

  unsigned int numVertices = 0;
  unsigned int numIndices = 0;

  for (unsigned int i = 0; i < _meshesData.size(); i++) {
    _meshesData[i].materialIndex = scene->mMeshes[i]->mMaterialIndex;
    _meshesData[i].numIndices = scene->mMeshes[i]->mNumFaces * 3;
    _meshesData[i].baseVertex = numVertices;
    _meshesData[i].baseIndex = numIndices;
    _meshesData[i].name = scene->mMeshes[i]->mName.data;

    numVertices += scene->mMeshes[i]->mNumVertices;
    numIndices += _meshesData[i].numIndices;
  }

  _vertices.reserve(numVertices);
  _indices.reserve(numIndices);

  for (unsigned int i = 0; i < _meshesData.size(); i++) {
    const aiMesh* mesh = scene->mMeshes[i];
    initMesh(i, mesh);
  }

  if (!initMaterials(scene, Filename)) {
    return false;
  }

  _animation.setScene(scene);
  _hasAnimation = scene->HasAnimations();

  glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vertex) * _vertices.size(),
               &_vertices[0],
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
    2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex),
                        (void*)offsetof(Vertex, texCoords));

  glEnableVertexAttribArray(3);
  glVertexAttribIPointer(
    3, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, IDs));

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(
    4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Weights));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesEbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(_indices[0]) * _indices.size(),
               &_indices[0],
               GL_STATIC_DRAW);

  glBindVertexArray(0);
  return (glGetError() == GL_NO_ERROR);
}

void Meshes::initMesh(unsigned int meshIndex, const aiMesh* mesh)
{
  const aiVector3D zeroes(0.0f, 0.0f, 0.0f);

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    const aiVector3D* pos = &(mesh->mVertices[i]);
    const aiVector3D* normal = &(mesh->mNormals[i]);
    const aiVector3D* texCoord =
      mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zeroes;

    auto vertex = Vertex();
    vertex.position = glm::vec3(pos->x, pos->y, pos->z);
    vertex.normal = glm::vec3(normal->x, normal->y, normal->z);
    vertex.texCoords = glm::vec2(texCoord->x, texCoord->y);
    _vertices.push_back(vertex);
  }

  loadBones(meshIndex, mesh);

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    const aiFace& Face = mesh->mFaces[i];
    for (unsigned int i = 0; i < Face.mNumIndices; ++i) {
      _indices.push_back(Face.mIndices[i]);
    }
  }
}

void Meshes::loadBones(unsigned int meshIndex, const aiMesh* mesh)
{
  for (unsigned int i = 0; i < mesh->mNumBones; i++) {
    unsigned int index = 0;
    string BoneName(mesh->mBones[i]->mName.data);

    if (_boneMapping.find(BoneName) == _boneMapping.end()) {
      index = _numBones;
      _numBones++;
      BoneData bd;
      _bonesData.push_back(bd);
      _bonesData[index].offset = mat4From4x4(mesh->mBones[i]->mOffsetMatrix);
      _boneMapping[BoneName] = index;
    } else {
      index = _boneMapping[BoneName];
    }

    for (unsigned int j = 0; j < mesh->mBones[i]->mNumWeights; j++) {
      unsigned int VertexID = _meshesData[meshIndex].baseVertex +
                              mesh->mBones[i]->mWeights[j].mVertexId;
      float Weight = mesh->mBones[i]->mWeights[j].mWeight;
      _vertices[VertexID].AddBoneData(index, Weight);
    }
  }
}

bool Meshes::initMaterials(const aiScene* pScene, const string& Filename)
{
  string::size_type SlashIndex = Filename.find_last_of("/");
  string Dir;

  if (SlashIndex == string::npos) {
    Dir = ".";
  } else if (SlashIndex == 0) {
    Dir = "/";
  } else {
    Dir = Filename.substr(0, SlashIndex);
  }

  bool res = true;

  for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
    const aiMaterial* material = pScene->mMaterials[i];

    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
      aiString Path;

      if (material->GetTexture(
            aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) ==
          AI_SUCCESS) {
        string p(Path.data);

        if (p.substr(0, 2) == ".\\") {
          p = p.substr(2, p.size() - 2);
        }

        string FullPath = Dir + "/" + p;

        _initialTextures[i] =
          std::make_shared<Texture>(GL_TEXTURE_2D, FullPath.c_str());

        if (!_initialTextures[i]->load()) {
          printf("Error loading texture '%s'\n", FullPath.c_str());
          res = false;
        } else {
          printf("%d - loaded texture '%s'\n", i, FullPath.c_str());
        }
      }
    }
  }

  return res;
}

void Meshes::deinit()
{
  if (_vertexVbo != 0) {
    glDeleteBuffers(1, &_vertexVbo);
    glDeleteBuffers(1, &_indicesEbo);
  }

  if (_vao != 0) {
    glDeleteVertexArrays(1, &_vao);
    _vao = 0;
  }
}

void Meshes::render()
{
  glBindVertexArray(_vao);

  for (unsigned int i = 0; i < _meshesData.size(); i++) {
    const unsigned int materialIndex = _meshesData[i].materialIndex;

    assert(materialIndex < _initialTextures.size());

    if (_initialTextures[materialIndex]->loaded()) {
      if (_texturesType == TexturePackType::Initial) {
        _initialTextures[materialIndex]->bind(GL_TEXTURE0);
      } else if (_texturesType == TexturePackType::OnSelection) {
        _onSelectionTextures[materialIndex]->bind(GL_TEXTURE0);
      } else if (_texturesType == TexturePackType::PreBuild) {
        _preBuildTextures[materialIndex]->bind(GL_TEXTURE0);
      } else if (_texturesType == TexturePackType::UnderFire) {
        _underFireTextures[materialIndex]->bind(GL_TEXTURE0);
      } else if (_texturesType == TexturePackType::Destroyed) {
        _destroyedTextures[materialIndex]->bind(GL_TEXTURE0);
      }
    }

    glDrawElementsBaseVertex(
      GL_TRIANGLES,
      _meshesData[i].numIndices,
      GL_UNSIGNED_INT,
      (void*)(sizeof(unsigned int) * _meshesData[i].baseIndex),
      _meshesData[i].baseVertex);
  }

  glBindVertexArray(0);
}

Meshes::Meshes() : _animation(_bonesData, _boneMapping, _numBones)
{
  _vao = 0;
  _vertexVbo = 0;
  _indicesEbo = 0;
  _numBones = 0;
  deinit();

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glGenBuffers(1, &_vertexVbo);
  glGenBuffers(1, &_indicesEbo);
}

Meshes::~Meshes()
{
  deinit();
}

void Meshes::loadTexture(const std::string& filename, TexturePackType type)
{
  if (type == TexturePackType::OnSelection) {
    _onSelectionTextures.clear();
    for (unsigned long i = 0; i < _initialTextures.size(); ++i) {
      _onSelectionTextures.push_back(
        std::make_shared<Texture>(GL_TEXTURE_2D, filename));
      _onSelectionTextures[i]->load();
    }
  } else if (type == TexturePackType::Initial) {
    auto s = _initialTextures.size();
    _initialTextures.clear();
    for (unsigned long i = 0; i < s; ++i) {
      _initialTextures.push_back(
        std::make_shared<Texture>(GL_TEXTURE_2D, filename));
      _initialTextures[i]->load();
    }
  } else if (type == TexturePackType::PreBuild) {
    auto s = _initialTextures.size();
    _preBuildTextures.clear();
    for (unsigned long i = 0; i < s; ++i) {
      _preBuildTextures.push_back(
        std::make_shared<Texture>(GL_TEXTURE_2D, filename));
      _preBuildTextures[i]->load();
    }
  } else if (type == TexturePackType::UnderFire) {
    auto s = _initialTextures.size();
    _underFireTextures.clear();
    for (unsigned long i = 0; i < s; ++i) {
      _underFireTextures.push_back(
        std::make_shared<Texture>(GL_TEXTURE_2D, filename));
      _underFireTextures[i]->load();
    }
  } else if (type == TexturePackType::Destroyed) {
    auto s = _initialTextures.size();
    _destroyedTextures.clear();
    for (unsigned long i = 0; i < s; ++i) {
      _destroyedTextures.push_back(
        std::make_shared<Texture>(GL_TEXTURE_2D, filename));
      _destroyedTextures[i]->load();
    }
  }
}

void Meshes::setActiveTexturesPack(TexturePackType type)
{
  _texturesType = type;
}

void Meshes::initSurface(float bottomLeftX,
                         float bottomLeftY,
                         float topRightX,
                         float topRightY,
                         int divisions,
                         std::string texturePath)
{
  _meshesData.resize(1);
  _initialTextures.resize(1);

  _meshesData[0].materialIndex = 0;
  _meshesData[0].numIndices = ::pow(divisions, 2) * 2 * 3;
  _meshesData[0].baseVertex = 0;
  _meshesData[0].baseIndex = 0;
  _meshesData[0].name = "surface";

  _vertices.reserve(::pow(divisions + 1, 2) * 3);
  float xStep = (topRightX - bottomLeftX) / divisions;
  float yStep = (topRightY - bottomLeftY) / divisions;

  auto noise = Noise(777, 256);
  for (int i = 0; i < divisions + 1; ++i) {
    for (int j = 0; j < divisions + 1; ++j) {
      Vertex vertex;
      vertex.position.x = bottomLeftX + static_cast<float>(i) * xStep;
      vertex.position.y = bottomLeftY + static_cast<float>(j) * yStep;
      /* vertex.position.z = 0.0f; */
      vertex.position.z =
        noise.eval(glm::vec2(vertex.position.x, vertex.position.y));

      vertex.texCoords.x = j % 2;
      vertex.texCoords.y = (i + 1) % 2;

      vertex.normal.x = 0.0f;
      vertex.normal.y = 0.0f;
      vertex.normal.z = 1.0f;

      _vertices.push_back(vertex);
    }
  }
  _indices.reserve(::pow(divisions, 2) * 2 * 3);
  int width = divisions + 1;
  for (int i = 0; i < divisions; ++i) {
    for (int j = 0; j < divisions; ++j) {
      _indices.push_back((i * width) + j);
      _indices.push_back((i * width) + j + 1);
      _indices.push_back((i * width) + j + width);

      _indices.push_back((i * width) + j + 1);
      _indices.push_back((i * width) + j + width);
      _indices.push_back((i * width) + j + width + 1);
    }
  }

  _initialTextures[0] =
    std::make_shared<Texture>(GL_TEXTURE_2D, texturePath.c_str());

  if (!_initialTextures[0]->load()) {
    printf("Error loading texture '%s'\n", texturePath.c_str());
  } else {
    printf("%d - loaded texture '%s'\n", 0, texturePath.c_str());
  }

  glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(Vertex) * _vertices.size(),
               &_vertices[0],
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
    2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex),
                        (void*)offsetof(Vertex, texCoords));

  glEnableVertexAttribArray(3);
  glVertexAttribIPointer(
    3, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, IDs));

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(
    4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Weights));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesEbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(_indices[0]) * _indices.size(),
               &_indices[0],
               GL_STATIC_DRAW);

  glBindVertexArray(0);
}

void Meshes::animate(Shader& shader, Animation::Type type, float percent)
{

  if (_hasAnimation) {
    _animation.animate(shader, type, percent);
  }
}
