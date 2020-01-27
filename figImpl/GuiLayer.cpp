#include <iomanip>

#include "../fig/globals.h"
#include "../logic/EventManager.h"
#include "ColonyWindow.h"
#include "GuiLayer.h"

#include "../fig/imgui/imgui.h"
#include "../fig/imgui/imgui_impl_glfw.h"
#include "../fig/imgui/imgui_impl_opengl3.h"

GuiLayer::GuiLayer(const Window::Param& param,
                   Window* window,
                   glm::mat4& view,
                   glm::mat4& projection) :
  _wParam(param),
  _window(window), _view(view), _projection(projection)
{
}

void GuiLayer::init()
{
}

void GuiLayer::update()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  logger.render();

  /* ImGui::Begin("camera"); */
  /* static float camera_z = 60.0f; */
  /* ImGui::SetWindowPos(ImVec2(0, 210)); */
  /* ImGui::SetWindowSize(ImVec2(500, 50)); */
  /* ImGui::SliderFloat("camera z", &camera_z, -100.0f, 100.0f); */
  /* ImGui::End(); */
  /* auto eye = _camera.eye(); */
  /* eye.z = camera_z; */
  /* _camera.setEye(eye); */

  /* ImGui::Begin("models scale"); */
  /* ImGui::SetWindowPos(ImVec2(0, 450)); */
  /* ImGui::SetWindowSize(ImVec2(200, 50)); */
  /* ImGui::SliderFloat("scale", &View::VIEW_SCALE, 0.0f, 1.0f); */
  /* ImGui::End(); */

  /* ImGui::Begin("light"); */
  /* static float x = 1.2; */
  /* static float y = 0.0; */
  /* static float z = 90.0; */
  /* ImGui::SetWindowPos(ImVec2(0, 110)); */
  /* ImGui::SetWindowSize(ImVec2(500, 100)); */
  /* ImGui::SliderFloat("light x", &x, -10.0f, 10.0f); */
  /* ImGui::SliderFloat("light y", &y, -10.0f, 10.0f); */
  /* ImGui::SliderFloat("light z", &z, -100.0f, 100.0f); */
  /* ImGui::End(); */
  /* _light->setPosition(glm::vec3(x, y, z)); */
}

void GuiLayer::render()
{
  showDebug();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiLayer::showDebug()
{
  auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
               ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs;
  ImGui::Begin("3dCoordinates", NULL, flags);
  ImGui::SetWindowPos(ImVec2(0, _wParam.height - 22));
  ImGui::SetWindowSize(ImVec2(500, 22));
  // TODO downcast
  auto pos = EventManager::unProject(
    dynamic_cast<ColonyWindow*>(_window), _view, _projection);
  std::stringstream ss;
  ss << "x:" << std::setw(5) << std::setprecision(2) << pos.x
     << "; y:" << std::setw(5) << std::setprecision(2) << pos.y
     << "; z: " << pos.z;
  ImGui::Text(ss.str().c_str());
  ImGui::End();
}
