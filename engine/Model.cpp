#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Model.h"

#include <GLFW/glfw3.h>

Model::Model(Shader& shader) : _shader(shader) {}

bool Model::load(const string& file)
{
  _scene =
    _importer.ReadFile(file.c_str(),
                       aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                         aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

  bool res = false;
  if (_scene) {
    res = init(_scene, file);
  } else {
    std::cout << "Error assimp file importer " << _importer.GetErrorString()
              << std::endl;
  }

  return res;
}

void Model::animate(Shader& shader, Animation::Type type, float percent)
{
  _meshes.animate(shader, type, percent);
}

bool Model::init(const aiScene* pScene, const string& Filename)
{
  return _meshes.initModel(pScene, Filename);
}

void Model::render()
{
  _shader.use();
  _meshes.render();
}

void Model::loadTexture(const std::string& filename, TexturePackType type)
{
  _meshes.loadTexture(filename, type);
}

void Model::setActiveTexturesPack(TexturePackType type)
{
  _meshes.setActiveTexturesPack(type);
}
