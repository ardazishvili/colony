#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

class Mesh
{
public:
  Mesh();
  virtual ~Mesh();
  Mesh(const Mesh&) = delete;
  Mesh(Mesh&&) = delete;
  Mesh& operator=(const Mesh&) = delete;
  Mesh& operator=(Mesh&&) = delete;

protected:
  void deinit();
  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
};

#endif
