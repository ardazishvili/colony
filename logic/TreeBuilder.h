#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "AbstractPlantBuilder.h"

class TreeBuilder : public AbstractPlantBuilder
{
public:
  TreeBuilder(fig::Shader& shader,
              Game* game,
              Barrier& barrier,
              fig::Terrain* terrain);
  void create() override;
  fig::MenuTextures getPreviewType() override;
};

#endif
