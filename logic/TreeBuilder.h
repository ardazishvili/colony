#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "AbstractUnitBuilder.h"
#include "Barrier.h"

class TreeBuilder : public AbstractUnitBuilder
{
public:
  TreeBuilder(Shader& shader, Game* game, Barrier& barrier, Terrain* terrain);
  void create() override;
  MenuTextures getPreviewType() override;

private:
  Shader& _shader;
  Game* _game;
  Barrier& _barrier;
  Terrain* _terrain;
};

#endif
