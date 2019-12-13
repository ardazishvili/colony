#include "ModelMesh.h"

bool ModelMesh::initModel(const aiScene* scene, const string& Filename)
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

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
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

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(_indices[0]) * _indices.size(),
               &_indices[0],
               GL_STATIC_DRAW);

  glBindVertexArray(0);
  return (glGetError() == GL_NO_ERROR);
}

void ModelMesh::initMesh(unsigned int meshIndex, const aiMesh* mesh)
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

void ModelMesh::loadBones(unsigned int meshIndex, const aiMesh* mesh)
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

bool ModelMesh::initMaterials(const aiScene* pScene, const string& Filename)
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

void ModelMesh::render()
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

ModelMesh::ModelMesh() : _animation(_bonesData, _boneMapping, _numBones)
{
  _numBones = 0;
}

void ModelMesh::loadTexture(const std::string& filename, TexturePackType type)
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

void ModelMesh::setActiveTexturesPack(TexturePackType type)
{
  _texturesType = type;
}

void ModelMesh::animate(Shader& shader, Animation::Type type, float percent)
{

  if (_hasAnimation) {
    _animation.animate(shader, type, percent);
  }
}

