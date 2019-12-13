#include "TerrainMesh.h"
#include <iostream>

void TerrainMesh::render()
{
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _v.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
