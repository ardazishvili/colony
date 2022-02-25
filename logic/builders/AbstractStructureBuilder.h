#pragma once

#include "figImpl/globals.h"
#include "logic/builders/AbstractBuilder.h"

class ColonyEventManager;
class AbstractStructureBuilder : public AbstractBuilder {
 public:
  AbstractStructureBuilder(ColonyEventManager* eventManager)
      : AbstractBuilder(), _eventManager(eventManager) {}

 protected:
  ColonyEventManager* _eventManager;
};
