#ifndef ABSTRACT_STRUCTURE_BUILDER_H
#define ABSTRACT_STRUCTURE_BUILDER_H

#include "../../figImpl/globals.h"

#include "AbstractBuilder.h"

class ColonyEventManager;
class AbstractStructureBuilder : public AbstractBuilder
{
public:
  AbstractStructureBuilder(Game* game, ColonyEventManager* eventManager) :
    AbstractBuilder(game), _eventManager(eventManager)
  {
  }
  virtual ~AbstractStructureBuilder() = default;

protected:
  ColonyEventManager* _eventManager;
};

#endif
