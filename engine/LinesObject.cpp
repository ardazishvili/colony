#include "LinesObject.h"

LinesObject::LinesObject(Shader& shader) : _shader(shader)
{
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenBuffers(1, &_vbo);
  glGenBuffers(1, &_ebo);
}

void LinesObject::initBuffers()
{
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(
    GL_ARRAY_BUFFER, sizeof(glm::vec3) * _v.size(), &_v[0], GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(_i[0]) * _i.size(),
               &_i[0],
               GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
}

void LinesObject::render()
{
  glBindVertexArray(_vao);
  glDrawElements(GL_LINES, indicesToRender(), GL_UNSIGNED_INT, 0);
}

unsigned int LinesObject::indicesToRender()
{
  return _i.size() * 2;
}
