#ifndef PANEL_H
#define PANEL_H

#include <GLFW/glfw3.h>

#include "../engine/Texture.h"
#include "PanelItem.h"

using PanelItems = std::vector<std::unique_ptr<PanelItem>>;

class Panel
{
public:
  enum class Type { Structures, Units };

  Panel(GLFWwindow* window, Type type, Shader& shader);

  void addItem(std::unique_ptr<PanelItem> item);
  void clear();
  bool isEmpty() const;
  void display();

  static const float PANEL_WIDTH;

private:
  GLFWwindow* _window;
  Type _type;
  Shader& _shader;
  PanelItems _items;
};

#endif
