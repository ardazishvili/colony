#include <iostream>

#include "../fig/ModelLoader.h"
#include "../fig/third/gui/imgui/imgui.h"

#include "../figImpl/globals.h"
#include "Panel.h"

using namespace std::string_literals;

Panel::Panel(fig::Window* window, Type type, fig::Shader& shader) : _window(window), _type(type), _shader(shader)
{
}

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
  auto config = CONFIG.get();
  ImGui::Begin(panelName.c_str());
  ImGui::SetWindowPos(ImVec2(_window->width() - config.panel_width, panelNo * _window->height() / 2));
  ImGui::SetWindowSize(ImVec2(config.panel_width, _window->height() / 2));
  for (unsigned long i = 0; i < _items.size(); ++i) {
    ImGui::PushID(i);
    if (ImGui::ImageButton((void*)(intptr_t)_items[i]->texture(),
                           ImVec2(config.panel_icon_size, config.panel_icon_size))) {
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
