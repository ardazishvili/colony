#include "SettingsGui.h"
#include "../fig/ImGuiBackend.h"

void SettingsGui::show()
{
  if (_visible) {
    ImGui::Begin("Settings",
                 &_visible,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    ImGui::SetWindowPos(
      ImVec2(_windowWidth / 2 - _width / 2, _windowHeight / 2 - _height / 2));
    ImGui::SetWindowSize(ImVec2(_width, _height));
    ImGui::End();
  }
}

void SettingsGui::toggle()
{
  _visible = !_visible;
}

SettingsGui::SettingsGui(int windowWidth, int windowHeight) :
  _windowWidth(windowWidth), _windowHeight(windowHeight)
{
}
