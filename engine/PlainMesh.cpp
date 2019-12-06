#include "PlainMesh.h"

PlainMesh::PlainMesh()
{
  _vao = 0;
  _vertexVbo = 0;
  _indicesEbo = 0;
  deinit();

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glGenBuffers(1, &_vertexVbo);
  glGenBuffers(1, &_indicesEbo);
}

PlainMesh::~PlainMesh()
{
  deinit();
}

void PlainMesh::initSurface(float bottomLeftX,
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
  for (int i = 0; i < divisions + 1; ++i) {
    for (int j = 0; j < divisions + 1; ++j) {
      Vertex vertex;
      vertex.position.x = bottomLeftX + static_cast<float>(i) * xStep;
      vertex.position.y = bottomLeftY + static_cast<float>(j) * yStep;
      vertex.position.z = 0.0f;

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

void PlainMesh::deinit()
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

void PlainMesh::render()
{
  glBindVertexArray(_vao);

  for (unsigned int i = 0; i < _meshesData.size(); i++) {
    const unsigned int materialIndex = _meshesData[i].materialIndex;

    assert(materialIndex < _initialTextures.size());

    _initialTextures[materialIndex]->bind(GL_TEXTURE0);

    glDrawElementsBaseVertex(
      GL_TRIANGLES,
      _meshesData[i].numIndices,
      GL_UNSIGNED_INT,
      (void*)(sizeof(unsigned int) * _meshesData[i].baseIndex),
      _meshesData[i].baseVertex);
  }

  glBindVertexArray(0);
}

void PlainMesh::loadTexture(const std::string& filename, TexturePackType type)
{
  auto s = _initialTextures.size();
  _initialTextures.clear();
  for (unsigned long i = 0; i < s; ++i) {
    _initialTextures.push_back(
      std::make_shared<Texture>(GL_TEXTURE_2D, filename));
    _initialTextures[i]->load();
  }
}
