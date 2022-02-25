#pragma once

#include "fig/ModelLoader.h"
#include "logic/builders/AbstractBuilder.h"

class PanelItem {
 public:
  PanelItem(std::unique_ptr<AbstractBuilder> builder);
  GLuint texture() const;
  AbstractBuilder* getBuilder();

 private:
  std::unique_ptr<AbstractBuilder> _builder;
  GLuint _textureId;
};
