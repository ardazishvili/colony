#ifndef PLANT_BUILDER_H
#define PLANT_BUILDER_H

#include "AbstractUnitBuilder.h"
#include "Barrier.h"

class PlantBuilder : public AbstractUnitBuilder
{
public:
  PlantBuilder(Shader& shader, Game& game, Barrier& barrier, Terrain* terrain);
  void create() override;
  MenuTextures getPreviewType() override;

private:
  Shader& _shader;
  Game& _game;
  Barrier& _barrier;
  Terrain* _terrain;
};

#endif
