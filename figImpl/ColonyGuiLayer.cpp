#include <iomanip>

#include "../fig/GlfwWindow.h"
#include "../fig/ImGuiBackend.h"
#include "../fig/globals.h"

#include "../figImpl/ColonyEventManager.h"

#include "ColonyGuiLayer.h"

ColonyGuiLayer::ColonyGuiLayer(const Window::Param& param,
                               Window* window,
                               glm::mat4& view,
                               glm::mat4& projection) :
  GuiLayer(window, std::make_unique<ImGuiBackend>()),
  _wParam(param), _view(view), _projection(projection)
{
}

void ColonyGuiLayer::init()
{
  _guiBack->init(_window);
}

void ColonyGuiLayer::update()
{
  _guiBack->newFrame();

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

void ColonyGuiLayer::render()
{
  showDebug();

  _guiBack->render();
}

void ColonyGuiLayer::showDebug()
{
  auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
               ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs;
  ImGui::Begin("3dCoordinates", NULL, flags);
  ImGui::SetWindowPos(ImVec2(0, _wParam.height - 22));
  ImGui::SetWindowSize(ImVec2(500, 22));
  auto pos = EventManager::unProject(_window, _view, _projection);
  std::stringstream ss;
  ss << "x:" << std::setw(5) << std::setprecision(2) << pos.x
     << "; y:" << std::setw(5) << std::setprecision(2) << pos.y
     << "; z: " << pos.z;
  ImGui::Text(ss.str().c_str());
  ImGui::End();
}

ColonyGuiLayer::~ColonyGuiLayer()
{
  _guiBack->shutdown();
}
