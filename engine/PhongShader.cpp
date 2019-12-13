#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../globals.h"
#include "PhongShader.h"

PhongShader::PhongShader(Light* light,
                         Camera& camera,
                         glm::mat4& view,
                         glm::mat4& projection,
                         const GLchar* vertexPath,
                         const GLchar* fragmentPath) :
  Shader(light, camera, view, projection, vertexPath, fragmentPath)
{
}

void PhongShader::configure()
{
  auto cameraPosition = _camera.reference();
  setVec3("viewPos", cameraPosition);
  // material properties
  setInt("material.diffuse", 0);
  setInt("material.specular", 1);
  setFloat("material.shininess", 64.0f);

  // light properties
  auto lightPosition = _light->position();
  setVec3("light.position", lightPosition);
  setVec3("light.ambient", 0.6f, 0.6f, 0.6f);
  setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
  setVec3("light.specular", 1.0f, 1.0f, 1.0f);

  setTransformation("view", glm::value_ptr(_view));
  setTransformation("projection", glm::value_ptr(_projection));
}
