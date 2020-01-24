#include <iostream>

#include "../fig/globals.h"
#include "PanelItem.h"

PanelItem::PanelItem(std::unique_ptr<AbstractBuilder> builder)
{
  _builder = std::move(builder);
  _textureId =
    modelLoader->menuTextures()[_builder->getPreviewType()]->getTextureId();
}

AbstractBuilder* PanelItem::getBuilder()
{
  return _builder.get();
}

GLuint PanelItem::texture() const
{
  return _textureId;
}
