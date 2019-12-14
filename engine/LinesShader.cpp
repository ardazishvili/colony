#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "LinesShader.h"

LinesShader::LinesShader(GLFWwindow* window,
                         Light* light,
                         Camera& camera,
                         glm::mat4& view,
                         glm::mat4& projection,
                         const GLchar* vertexPath,
                         const GLchar* fragmentPath) :
  Shader(light, camera, view, projection, vertexPath, fragmentPath),
  _window(window)
{
}

void LinesShader::configure()
{
  setTransformation("view", glm::value_ptr(_view));
  setTransformation("projection", glm::value_ptr(_projection));
  int x, y;
  glfwGetWindowSize(_window, &x, &y);
  glm::vec2 resolution(x, y);
  setVec2("resolution", resolution);
}
