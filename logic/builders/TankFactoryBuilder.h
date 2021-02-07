#ifndef TANK_FACTORY_BUILDER_H
#define TANK_FACTORY_BUILDER_H

#include "AbstractStructureBuilder.h"

class TankFactoryBuilder : public AbstractStructureBuilder
{
public:
  TankFactoryBuilder(Game* game, ColonyEventManager* eventManager, fig::AStar* router);
  ~TankFactoryBuilder();

  void create() override;
  fig::MenuTextures getPreviewType() override;

private:
  fig::AStar* _router;
};

#endif
