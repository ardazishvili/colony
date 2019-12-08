#ifndef SKYBOX_SHADER_H
#define SKYBOX_SHADER_H

#include "Shader.h"

class SkyboxShader : public Shader
{
public:
  SkyboxShader(const GLchar* vertexPath, const GLchar* fragmentPath);
  void configure() override;
};

#endif
