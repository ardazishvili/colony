#pragma once

#include "fig/Terrain.h"
#include "fig/math/AStar.h"
#include "logic/builders/AbstractStructureBuilder.h"

struct AStar;
class HqBuilder : public AbstractStructureBuilder {
 public:
  HqBuilder(ColonyEventManager* eventManager, fig::Terrain& terrain,
            fig::AStar& router);
  ~HqBuilder();

  void addToGame(Game& game) override;
  fig::MenuTextures getPreviewType() override;

 private:
  fig::Terrain& _terrain;
  fig::AStar& _router;
};
