#include <chrono>
#include <iomanip>
#include <optional>

#include "../fig/globals.h"

#include "../figImpl/ColonyEventManager.h"
#include "globals.h"

#include "ColonyGuiLayer.h"

void ColonyGuiLayer::init()
{
  _guiBack->init(_window);
}

void ColonyGuiLayer::update()
{
  _guiBack->newFrame();

  auto config = CONFIG.get();
  if (config.show_log) {
    fig::logger.render();
  }

  ImGui::Begin("camera");
  static float camera_z = 60.0f;
  ImGui::SetWindowPos(ImVec2(0, 210));
  ImGui::SetWindowSize(ImVec2(500, 50));
  ImGui::SliderFloat("camera z", &camera_z, -100.0f, 100.0f);
  ImGui::End();
  auto eye = _camera->eye();
  eye.z = camera_z;
  _camera->setEye(eye);

  ImGui::Begin("models scale");
  ImGui::SetWindowPos(ImVec2(0, 450));
  ImGui::SetWindowSize(ImVec2(200, 50));
  ImGui::SliderFloat("scale", &View::VIEW_SCALE, 0.0f, 1.0f);
  ImGui::End();

  ImGui::Begin("light");
  static float x = 1.2;
  static float y = 0.0;
  static float z = 90.0;
  ImGui::SetWindowPos(ImVec2(0, 110));
  ImGui::SetWindowSize(ImVec2(500, 100));
  ImGui::SliderFloat("light x", &x, -10.0f, 10.0f);
  ImGui::SliderFloat("light y", &y, -10.0f, 10.0f);
  ImGui::SliderFloat("light z", &z, -100.0f, 100.0f);
  ImGui::End();
  _light->setPosition(glm::vec3(x, y, z));

  ImGui::Begin("Flat/Globe view");
  ImGui::SetWindowPos(ImVec2(0, 740));
  ImGui::SetWindowSize(ImVec2(200, 40));
  ImGui::Checkbox("state", &flatView);
  ImGui::End();

  ImGui::Begin("Configuration",
               NULL,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar);
  ImGui::SetWindowPos(ImVec2(_window->width() - config.panel_width - config.settings_icon_size - 6, 0));
  ImGui::SetWindowSize(ImVec2(config.settings_icon_size + 6, config.settings_icon_size + 6));
  if (ImGui::ImageButton((void*)(intptr_t)fig::modelLoader->menuTextures()[fig::MenuTextures::Wheel]->getTextureId(),
                         ImVec2(config.settings_icon_size, config.settings_icon_size))) {
    _settingsGui.toggle();
  }
  ImGui::End();

  _settingsGui.show();
}

void ColonyGuiLayer::render()
{
  ++_frameCount;
  auto now =
    std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  if (now - _prev_time > 1.0) {
    _fps = _frameCount;
    _frameCount = 0;
    _prev_time = now;
  }
  showDebug();

  _guiBack->render();
}

void ColonyGuiLayer::showDebug()
{
  auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs;
  ImGui::Begin("3dCoordinates", NULL, flags);
  ImGui::SetWindowPos(ImVec2(0, _window->height() - 22));
  ImGui::SetWindowSize(ImVec2(250, 22));
  auto pos = fig::EventManager::unProject(_window, _view, _projection);
  std::stringstream ss;
  ss << "x:" << std::setw(5) << std::setprecision(2) << pos.x << "; y:" << std::setw(5) << std::setprecision(2) << pos.y
     << "; z: " << pos.z;
  ImGui::Text("%s", ss.str().c_str());
  ImGui::End();

  ImGui::Begin("fps", NULL, flags);
  ImGui::SetWindowPos(ImVec2(250, _window->height() - 22));
  ImGui::SetWindowSize(ImVec2(50, 22));
  ImGui::Text("FPS: %s", std::to_string(_fps).c_str());
  ImGui::End();
}

ColonyGuiLayer::~ColonyGuiLayer()
{
  _guiBack->shutdown();
}
