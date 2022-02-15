#pragma once

#include "logic/builders/AbstractStructureBuilder.h"

class TurbineBuilder : public AbstractStructureBuilder {
 public:
  TurbineBuilder(ColonyEventManager* eventManager);

  void addToGame(Game& game) override;
  fig::MenuTextures getPreviewType() override;
};
