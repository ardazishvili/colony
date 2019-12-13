#ifndef ABSTRACT_STRUCTURE_BUILDER_H
#define ABSTRACT_STRUCTURE_BUILDER_H

#include "AbstractBuilder.h"
/* #include "EventManager.h" */

class EventManager;
class AbstractStructureBuilder : public AbstractBuilder
{
public:
  AbstractStructureBuilder(Game* game, EventManager* eventManager) :
    AbstractBuilder(game), _eventManager(eventManager)
  {
  }
  virtual ~AbstractStructureBuilder() = default;

protected:
  EventManager* _eventManager;
};

#endif
