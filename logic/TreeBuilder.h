#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "AbstractPlantBuilder.h"

class TreeBuilder : public AbstractPlantBuilder
{
public:
  TreeBuilder(Shader& shader, Game* game, Barrier& barrier, Terrain* terrain);
  void create() override;
  MenuTextures getPreviewType() override;
};

#endif
