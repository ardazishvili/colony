#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "Light.h"
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

  static float b = 0.5;
  static float e = 8.8;
  static float h = 0.0f;
  ImGui::Begin("fog");
  ImGui::SetWindowPos(ImVec2(0, 710));
  ImGui::SetWindowSize(ImVec2(200, 85));
  ImGui::SliderFloat("b", &b, 0.0f, 10.0f);
  ImGui::SliderFloat("e", &e, 0.0f, 10.0f);
  ImGui::SliderFloat("h", &h, 0.0f, 2.0f);
  ImGui::End();
  auto cp = _camera.eye();
  setVec3("camPosition", cp);

  setFloat("b", b);
  setFloat("e", e);
  setFloat("h", h);

  setTransformation("view", glm::value_ptr(_view));
  setTransformation("projection", glm::value_ptr(_projection));
}
