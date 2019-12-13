#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

class Mesh
{
public:
  Mesh();
  ~Mesh();

protected:
  void deinit();
  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
};

#endif
