#pragma once

#include "fig/types.h"

class Game;

class AbstractBuilder {
 public:
  AbstractBuilder() = default;
  AbstractBuilder(const AbstractBuilder&) = delete;
  AbstractBuilder(AbstractBuilder&&) = delete;
  AbstractBuilder& operator=(const AbstractBuilder&) = delete;
  AbstractBuilder& operator=(AbstractBuilder&&) = delete;
  virtual ~AbstractBuilder() = default;

  virtual void addToGame(Game& game) = 0;
  virtual fig::MenuTextures getPreviewType() = 0;
};
