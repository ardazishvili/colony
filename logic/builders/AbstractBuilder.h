#ifndef ABSTRACT_BUILDER_H
#define ABSTRACT_BUILDER_H

#include "memory"

#include <glm/glm.hpp>

#include "../../fig/ModelLoader.h"

class Game;
class BuildableStructure;

class AbstractBuilder
{
public:
  AbstractBuilder(Game* game) : _game(game)
  {
  }

  virtual void create() = 0;
  virtual fig::MenuTextures getPreviewType() = 0;

  ~AbstractBuilder() = default;
  AbstractBuilder(const AbstractBuilder&) = delete;
  AbstractBuilder(AbstractBuilder&&) = delete;
  AbstractBuilder& operator=(const AbstractBuilder&) = delete;
  AbstractBuilder& operator=(AbstractBuilder&&) = delete;

protected:
  Game* _game;
};

#endif
