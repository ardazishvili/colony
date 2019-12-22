#ifndef PLANT_BUILDER_H
#define PLANT_BUILDER_H

#include "AbstractPlantBuilder.h"

class PlantBuilder : public AbstractPlantBuilder
{
public:
  PlantBuilder(Shader& shader, Game* game, Barrier& barrier, Terrain* terrain);
  void create() override;
  MenuTextures getPreviewType() override;
};

#endif
