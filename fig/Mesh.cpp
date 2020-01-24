#include "Mesh.h"

Mesh::Mesh()
{
  _vao = 0;
  _vbo = 0;
  _ebo = 0;
  deinit();

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glGenBuffers(1, &_vbo);
  glGenBuffers(1, &_ebo);
}

Mesh::~Mesh()
{
  deinit();
}

void Mesh::deinit()
{
  if (_vbo != 0) {
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
  }

  if (_vao != 0) {
    glDeleteVertexArrays(1, &_vao);
    _vao = 0;
  }
}
