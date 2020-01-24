#ifndef SKYBOX_SHADER_H
#define SKYBOX_SHADER_H

#include "Shader.h"

class SkyboxShader : public Shader
{
public:
  SkyboxShader(Light* light,
               Camera& camera,
               glm::mat4& view,
               glm::mat4& projection,
               const GLchar* vertexPath,
               const GLchar* fragmentPath);
  void configure() override;
};

#endif
