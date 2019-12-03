#ifndef ABSTRACT_BUILDER_H
#define ABSTRACT_BUILDER_H

#include "memory"

#include <glm/glm.hpp>

#include "../engine/ModelLoader.h"

class BuildableStructure;

class AbstractBuilder
{
public:
  virtual void create() = 0;
  virtual MenuTextures getPreviewType() = 0;
  ~AbstractBuilder() = default;
};

#endif
