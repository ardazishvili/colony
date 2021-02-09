#ifndef BARRIER_BUILDER_H
#define BARRIER_BUILDER_H

#include "../../fig/Terrain.h"
#include "AbstractStructureBuilder.h"

class BarrierBuilder : public AbstractStructureBuilder
{
public:
  BarrierBuilder(Game* game, ColonyEventManager* eventManager, fig::Terrain* terrain);

  void create() override;
  fig::MenuTextures getPreviewType() override;

private:
  fig::Terrain* _terrain;
};

#endif
