#ifndef TURBINE_BUILDER_H
#define TURBINE_BUILDER_H

#include "AbstractStructureBuilder.h"

class TurbineBuilder : public AbstractStructureBuilder
{
public:
  TurbineBuilder(Game* game, ColonyEventManager* eventManager);

  void create() override;
  fig::MenuTextures getPreviewType() override;
};

#endif
