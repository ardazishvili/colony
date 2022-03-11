#include "figImpl/SettingsGui.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "fig/ImGuiBackend.h"
#include "figImpl/globals.h"
#include "third/gui/imgui/imgui.h"

std::vector<std::string> options = {"A", "B", "C", "D", "E", "F", "G", "H", "I",
                                    "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                                    "S", "T", "U", "V", "W", "X", "Y", "Z"};

void SettingsGui::show() {
  if (_visible) {
    auto config = CONFIG.get();

    ImGui::Begin("Settings", &_visible,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

    ImGui::SetWindowPos(
        ImVec2(_windowWidth / 2 - _width / 2, _windowHeight / 2 - _height / 2));
    ImGui::SetWindowSize(ImVec2(_width, _height));
    if (ImGui::BeginTable("settings", 2)) {
      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::Text("Screen size");
      ImGui::TableSetColumnIndex(1);
      auto current_screen_size = std::to_string(config.window_width) + "x" +
                                 std::to_string(config.window_height);
      auto it = std::find_if(config.screenSizes.begin(),
                             config.screenSizes.end(), [config](const auto& p) {
                               return p.first == config.window_width &&
                                      p.second == config.window_height;
                             });
      std::vector<std::string> resolutions;
      std::transform(config.screenSizes.begin(), config.screenSizes.end(),
                     std::back_inserter(resolutions), [](const auto& p) {
                       return std::to_string(p.first) + "x" +
                              std::to_string(p.second);
                     });

      static ImGuiComboFlags flags = 0;
      static int selectedResolution =
          std::distance(config.screenSizes.begin(), it);
      const char* resolutions_preview_value =
          resolutions[selectedResolution].c_str();

      if (ImGui::BeginCombo("combo 1", resolutions_preview_value, flags)) {
        for (int n = 0; n < resolutions.size(); n++) {
          const bool is_selected = (selectedResolution == n);
          if (ImGui::Selectable(resolutions[n].c_str(), is_selected)) {
            selectedResolution = n;
            CONFIG.write("window_width",
                         config.screenSizes.at(selectedResolution).first);
            CONFIG.write("window_height",
                         config.screenSizes.at(selectedResolution).second);
          }

          if (is_selected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }

      auto controls_size = config.controls.size();
      std::vector<int> selected(controls_size);
      std::vector<std::string> preview_value(controls_size);

      auto end = config.controls.end();
      for (auto it = config.controls.begin(); it != end; ++it) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text(it->first.c_str());

        ImGui::TableSetColumnIndex(1);
        auto i = std::distance(config.controls.begin(), it);
        auto o_it = std::find_if(
            options.begin(), options.end(),
            [config, &it](const auto& option) { return option == it->second; });
        selected[i] = std::distance(options.begin(), o_it);
        preview_value[i] = options[selected[i]].c_str();
        auto combo_name = "combo_ctrl_" + std::to_string(i);
        if (ImGui::BeginCombo(combo_name.c_str(), preview_value[i].c_str(),
                              flags)) {
          for (int n = 0; n < options.size(); n++) {
            const bool is_selected = (selected[i] == n);
            if (ImGui::Selectable(options[n].c_str(), is_selected)) {
              selected[i] = n;
              it->second = options.at(selected[i]);
              CONFIG.write("controls", config.controls);
              CONFIG.read();
            }

            if (is_selected) {
              ImGui::SetItemDefaultFocus();
            }
          }
          ImGui::EndCombo();
        }
      }

      ImGui::EndTable();
    }
    ImGui::End();
  }
}

void SettingsGui::toggle() { _visible = !_visible; }

SettingsGui::SettingsGui(int windowWidth, int windowHeight)
    : _windowWidth(windowWidth), _windowHeight(windowHeight) {}
