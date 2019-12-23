#ifndef BARRIER_BUILDER_H
#define BARRIER_BUILDER_H

#include "../engine/Terrain.h"
#include "AbstractStructureBuilder.h"

class BarrierBuilder : public AbstractStructureBuilder
{
public:
  BarrierBuilder(Game* game,
                 EventManager* eventManager,
                 Shader& textureShader,
                 Shader& linesShader,
                 Terrain* terrain);

  void create() override;
  MenuTextures getPreviewType() override;

private:
  Terrain* _terrain;
};

#endif
