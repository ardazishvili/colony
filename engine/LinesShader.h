#ifndef LINES_SHADER_H
#define LINES_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class LinesShader : public Shader
{

public:
  LinesShader(GLFWwindow* window,
              Light* light,
              Camera& camera,
              glm::mat4& view,
              glm::mat4& projection,
              const GLchar* vertexPath,
              const GLchar* fragmentPath);
  void configure() override;

private:
  GLFWwindow* _window;
};

#endif
