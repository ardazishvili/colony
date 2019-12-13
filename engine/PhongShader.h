#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include <glm/glm.hpp>

#include "Shader.h"

class PhongShader : public Shader
{
public:
  PhongShader(glm::mat4& view,
              glm::mat4& projection,
              const GLchar* vertexPath,
              const GLchar* fragmentPath);
  void configure() override;
};

#endif
