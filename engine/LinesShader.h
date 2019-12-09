#ifndef LINES_SHADER_H
#define LINES_SHADER_H

#include "Shader.h"

class LinesShader : public Shader
{

public:
  LinesShader(const GLchar* vertexPath, const GLchar* fragmentPath);
  void configureRender();
  void configure(){};

private:
  unsigned int _vao;
  unsigned int _vbo;
};

#endif
