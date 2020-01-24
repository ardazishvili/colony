#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "LinesShader.h"

LinesShader::LinesShader(Light* light,
                         Camera& camera,
                         glm::mat4& view,
                         glm::mat4& projection,
                         const GLchar* vertexPath,
                         const GLchar* fragmentPath) :
  Shader(light, camera, view, projection, vertexPath, fragmentPath)
{
}

void LinesShader::configure()
{
  setTransformation("view", glm::value_ptr(_view));
  setTransformation("projection", glm::value_ptr(_projection));
}
