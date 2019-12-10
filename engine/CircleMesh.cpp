#include "CircleMesh.h"

CircleMesh::CircleMesh()
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

CircleMesh::~CircleMesh()
{
  deinit();
}

void CircleMesh::deinit()
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

void CircleMesh::render()
{
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _v.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void CircleMesh::init(float radius, unsigned int divisions)
{
  _v.reserve(divisions + 1);
  auto vertex = VertexColor();
  vertex.p.x = 0.0f;
  vertex.p.y = 0.0f;
  vertex.p.z = 0.0f;
  vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
  vertex.color = glm::vec3(0.0f, 1.0f, 0.0f);
  _v.push_back(vertex);
  for (unsigned int i = 0; i < divisions; ++i) {
    auto vertex = VertexColor();
    vertex.p.x = radius * ::cos(i * M_PI * 2 / divisions);
    vertex.p.y = radius * ::sin(i * M_PI * 2 / divisions);
    vertex.p.z = 0.0f;
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertex.color = glm::vec3(0.0f, 1.0f, 0.0f);
    _v.push_back(vertex);
  }

  _indices.reserve(divisions);
  for (unsigned int i = 0; i < divisions - 1; ++i) {
    _indices.push_back(0);
    _indices.push_back(i + 1);
    _indices.push_back(i + 2);
  }
  _indices.push_back(0);
  _indices.push_back(divisions);
  _indices.push_back(1);

  glBindBuffer(GL_ARRAY_BUFFER, _vertexVbo);
  glBufferData(
    GL_ARRAY_BUFFER, sizeof(VertexColor) * _v.size(), &_v[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(VertexColor),
                        (void*)offsetof(VertexColor, color));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(VertexColor),
                        (void*)offsetof(VertexColor, normal));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesEbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(_indices[0]) * _indices.size(),
               &_indices[0],
               GL_STATIC_DRAW);

  glBindVertexArray(0);
}
