#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include "Shader.h"

class PhongShader : public Shader
{
public:
  PhongShader(const GLchar* vertexPath, const GLchar* fragmentPath);

  void configure() override;

private:
};

#endif
