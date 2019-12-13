#ifndef LINES_SHADER_H
#define LINES_SHADER_H

#include "Shader.h"

class LinesShader : public Shader
{

public:
  LinesShader(Light* light,
              Camera& camera,
              glm::mat4& view,
              glm::mat4& projection,
              const GLchar* vertexPath,
              const GLchar* fragmentPath);
  void configureRender();
  void configure() override{};

private:
  unsigned int _vao;
  unsigned int _vbo;
};

#endif
