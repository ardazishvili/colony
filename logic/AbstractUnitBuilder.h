#ifndef ABSTRACT_UNIT_BUILDER_H
#define ABSTRACT_UNIT_BUILDER_H

#include "AbstractBuilder.h"

class AbstractUnitBuilder : public AbstractBuilder
{
public:
  AbstractUnitBuilder(Game* game) : AbstractBuilder(game)
  {
  }
  virtual void create() = 0;

  virtual ~AbstractUnitBuilder() = default;
};

#endif
