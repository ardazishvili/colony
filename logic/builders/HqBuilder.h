#ifndef HQ_BUILDER_H
#define HQ_BUILDER_H

#include "../../fig/Terrain.h"
#include "AbstractStructureBuilder.h"

struct AStar;
class HqBuilder : public AbstractStructureBuilder
{
public:
  HqBuilder(Game* game, ColonyEventManager* eventManager, fig::Terrain* terrain, fig::AStar* router);
  ~HqBuilder();

  void create() override;
  fig::MenuTextures getPreviewType() override;

private:
  fig::Terrain* _terrain;
  fig::AStar* _router;
};

#endif
