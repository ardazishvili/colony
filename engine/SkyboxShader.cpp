#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../globals.h"
#include "SkyboxShader.h"

SkyboxShader::SkyboxShader(const GLchar* vertexPath,
                           const GLchar* fragmentPath) :
  Shader(vertexPath, fragmentPath)
{}

void SkyboxShader::configure()
{
  auto view = glm::mat4(glm::mat3(gView));
  setTransformation("view", glm::value_ptr(view));
  setTransformation("projection", glm::value_ptr(gProjection));
  setInt("skybox", 0);
}
