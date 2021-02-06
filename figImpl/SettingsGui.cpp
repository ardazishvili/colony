#include <algorithm>
#include <iterator>
#include <string>

#include "../fig/ImGuiBackend.h"

#include "SettingsGui.h"
#include "globals.h"

static auto vector_getter = [](void* vec, int idx, const char** out_text) {
  auto& vector = *static_cast<std::vector<std::string>*>(vec);
  if (idx < 0 || idx >= static_cast<int>(vector.size())) {
    return false;
  }
  *out_text = vector.at(idx).c_str();
  return true;
};

void SettingsGui::show()
{
  if (_visible) {
    ImGui::Begin("Settings", &_visible, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    ImGui::SetWindowPos(ImVec2(_windowWidth / 2 - _width / 2, _windowHeight / 2 - _height / 2));
    ImGui::SetWindowSize(ImVec2(_width, _height));
    ImGui::SetNextWindowContentWidth(200);
    ImGui::Columns(2, "Screen size");
    ImGui::TextUnformatted("Screen size");
    ImGui::NextColumn();
    auto config = CONFIG.get();
    auto current_screen_size = std::to_string(config.window_width) + "x" + std::to_string(config.window_height);
    auto it = std::find_if(config.screenSizes.begin(), config.screenSizes.end(), [config](const auto& p) {
      return p.first == config.window_width && p.second == config.window_height;
    });
    static int selectedResolution = std::distance(config.screenSizes.begin(), it);
    std::vector<std::string> resolutions;
    std::transform(
      config.screenSizes.begin(), config.screenSizes.end(), std::back_inserter(resolutions), [](const auto& p) {
        return std::to_string(p.first) + "x" + std::to_string(p.second);
      });
    if (ImGui::Combo("", &selectedResolution, vector_getter, static_cast<void*>(&resolutions), resolutions.size())) {
      CONFIG.write("window_width", config.screenSizes.at(selectedResolution).first);
      CONFIG.write("window_height", config.screenSizes.at(selectedResolution).second);
    }
    ImGui::End();
  }
}

void SettingsGui::toggle()
{
  _visible = !_visible;
}

SettingsGui::SettingsGui(int windowWidth, int windowHeight) : _windowWidth(windowWidth), _windowHeight(windowHeight)
{
}
