#include "LinesShader.h"

LinesShader::LinesShader(const GLchar* vertexPath, const GLchar* fragmentPath) :
  Shader(vertexPath, fragmentPath)
{}

void LinesShader::configureRender()
{
  /* float verts[] = { 1, 1, 1, 0, 0, 0 }; */
  /* float verts[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f
   * }; */
  /* float verts[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f }; */
  float verts[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
                    -0.5f, 0.5f,  0.0f, 0.5f, 0.5f,  0.0f };
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);
  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glUseProgram(_id);

  glBindVertexArray(_vao);
  glDrawArrays(GL_LINES, 0, 4);
}
