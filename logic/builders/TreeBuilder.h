#pragma once

#include "logic/builders/AbstractPlantBuilder.h"

class TreeBuilder : public AbstractPlantBuilder {
 public:
  TreeBuilder(Barrier& barrier, fig::Terrain& terrain);
  void addToGame(Game& game) override;
  fig::MenuTextures getPreviewType() override;
};
