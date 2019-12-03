#ifndef PANEL_H
#define PANEL_H

#include "../engine/Texture.h"
#include "PanelItem.h"

using PanelItems = std::vector<std::unique_ptr<PanelItem>>;

class Panel
{
public:
  enum class Type
  {
    Structures,
    Units
  };

  Panel(Type type, Shader& shader);

  void addItem(std::unique_ptr<PanelItem> item);
  void clear();
  bool isEmpty() const;
  void display();

  static const float PANEL_WIDTH;

private:
  Type _type;
  Shader& _shader;
  PanelItems _items;
};

#endif
