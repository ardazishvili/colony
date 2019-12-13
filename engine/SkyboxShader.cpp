#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../globals.h"
#include "SkyboxShader.h"

SkyboxShader::SkyboxShader(glm::mat4& view,
                           glm::mat4& projection,
                           const GLchar* vertexPath,
                           const GLchar* fragmentPath) :
  Shader(view, projection, vertexPath, fragmentPath)
{
}

void SkyboxShader::configure()
{
  auto v = glm::mat4(glm::mat3(_view));
  setTransformation("view", glm::value_ptr(v));
  setTransformation("projection", glm::value_ptr(_projection));
  setInt("skybox", 0);
}
