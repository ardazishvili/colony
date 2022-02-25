#pragma once

#include "fig/math/AStar.h"
#include "logic/builders/AbstractStructureBuilder.h"

class TankFactoryBuilder : public AbstractStructureBuilder {
 public:
  TankFactoryBuilder(ColonyEventManager* eventManager, fig::AStar& router);
  ~TankFactoryBuilder();

  void addToGame(Game& game) override;
  fig::MenuTextures getPreviewType() override;

 private:
  fig::AStar& _router;
};
