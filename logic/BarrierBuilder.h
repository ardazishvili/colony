#ifndef BARRIER_BUILDER_H
#define BARRIER_BUILDER_H

#include "../fig/Terrain.h"
#include "../fig/math/AStar.h"
#include "AbstractStructureBuilder.h"

class BarrierBuilder : public AbstractStructureBuilder
{
public:
  BarrierBuilder(Game* game,
                 EventManager* eventManager,
                 Shader& textureShader,
                 Shader& linesShader,
                 Terrain* terrain,
                 AStar* astar);

  void create() override;
  MenuTextures getPreviewType() override;

private:
  Terrain* _terrain;
  AStar* _astar;
};

#endif
