#ifndef PANEL_ITEM_H
#define PANEL_ITEM_H

#include "../engine/ModelLoader.h"
#include "AbstractBuilder.h"

class PanelItem
{
public:
  PanelItem(std::unique_ptr<AbstractBuilder> builder);
  GLuint texture() const;
  AbstractBuilder* getBuilder();

private:
  std::unique_ptr<AbstractBuilder> _builder;
  GLuint _textureId;
};

#endif
