#ifndef PANEL_H
#define PANEL_H

#include <GLFW/glfw3.h>

#include "../fig/Texture.h"
#include "../fig/Window.h"
#include "PanelItem.h"

using PanelItems = std::vector<std::unique_ptr<PanelItem>>;

class Panel
{
public:
  enum class Type { Structures, Units };

  Panel(fig::Window* window, Type type, fig::Shader& shader);

  void addItem(std::unique_ptr<PanelItem> item);
  void clear();
  bool isEmpty() const;
  void display();

private:
  fig::Window* _window;
  Type _type;
  fig::Shader& _shader;
  PanelItems _items;
};

#endif
