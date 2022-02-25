#pragma once

#include "fig/Texture.h"
#include "fig/Window.h"
#include "logic/PanelItem.h"

using PanelItems = std::vector<std::unique_ptr<PanelItem>>;

class Panel {
 public:
  enum class Type { Structures, Units };

  Panel(fig::Window& window, Game& game, Type type);

  void addItem(std::unique_ptr<PanelItem> item);
  void clear();
  bool isEmpty() const;
  void display();

 private:
  fig::Window& _window;
  Game& _game;
  Type _type;
  PanelItems _items;
};
