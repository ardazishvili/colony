#ifndef ABSTRACT_UNIT_BUILDER_H
#define ABSTRACT_UNIT_BUILDER_H

#include <SFML/Graphics/Sprite.hpp>

#include "AbstractBuilder.h"

class AbstractUnitBuilder : public AbstractBuilder {
public:
  virtual void create() = 0;

  virtual ~AbstractUnitBuilder() = default;
};

#endif
