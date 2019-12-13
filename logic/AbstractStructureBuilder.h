#ifndef ABSTRACT_STRUCTURE_BUILDER_H
#define ABSTRACT_STRUCTURE_BUILDER_H

#include "AbstractBuilder.h"

class AbstractStructureBuilder : public AbstractBuilder
{
public:
  AbstractStructureBuilder(Game* game) : AbstractBuilder(game)
  {
  }
  virtual ~AbstractStructureBuilder() = default;
};

#endif
