#pragma once

#include "logic/builders/AbstractPlantBuilder.h"

class PlantBuilder : public AbstractPlantBuilder {
 public:
  PlantBuilder(Barrier& barrier, fig::Terrain& terrain);

  void addToGame(Game& game) override;
  fig::MenuTextures getPreviewType() override;
};
