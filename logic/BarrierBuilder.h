#ifndef BARRIER_BUILDER_H
#define BARRIER_BUILDER_H

#include "../engine/Terrain.h"
#include "AbstractStructureBuilder.h"

class BarrierBuilder : public AbstractStructureBuilder
{
public:
  BarrierBuilder(Game* game,
                 EventManager* eventManager,
                 Shader& shader,
                 Terrain* terrain);

  void create() override;
  MenuTextures getPreviewType() override;

private:
  Shader& _shader;
  Terrain* _terrain;
};

#endif
