#pragma once

#include "fig/Terrain.h"
#include "fig/math/AStar.h"
#include "logic/builders/AbstractStructureBuilder.h"

class BarrierBuilder : public AbstractStructureBuilder {
 public:
  BarrierBuilder(ColonyEventManager* eventManager, fig::Terrain& terrain,
                 fig::AStar& astar);

  void addToGame(Game& game) override;
  fig::MenuTextures getPreviewType() override;

 private:
  fig::Terrain& _terrain;
  fig::AStar& _astar;
};
