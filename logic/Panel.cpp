#include <iostream>

#include "../imgui/imgui.h"

#include "../engine/ModelLoader.h"
#include "../globals.h"
#include "Panel.h"

using namespace std::string_literals;
const float Panel::PANEL_WIDTH = 300;

Panel::Panel(Type type, Shader& shader) : _type(type), _shader(shader) {}

void Panel::addItem(std::unique_ptr<PanelItem> item)
{
  _items.push_back(std::move(item));
}

void Panel::clear()
{
  _items.clear();
}

void Panel::display()
{
  auto panelNo = static_cast<int>(_type);
  auto panelName = "Panel #"s + std::to_string(panelNo);
  ImGui::Begin(panelName.c_str());
  ImGui::SetWindowPos(
    ImVec2(screenWidth - PANEL_WIDTH, panelNo * screenHeight / 2));
  ImGui::SetWindowSize(ImVec2(PANEL_WIDTH, screenHeight / 2));
  for (unsigned long i = 0; i < _items.size(); ++i) {
    ImGui::PushID(i);
    if (ImGui::ImageButton((void*)(intptr_t)_items[i]->texture(),
                           ImVec2(80, 80))) {
      _items[i]->getBuilder()->create();
    }
    ImGui::PopID();
    ImGui::SameLine();
  }
  ImGui::End();
}

bool Panel::isEmpty() const
{
  return _items.empty();
}
