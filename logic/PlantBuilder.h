#ifndef PLANT_BUILDER_H
#define PLANT_BUILDER_H

#include "AbstractPlantBuilder.h"

class PlantBuilder : public AbstractPlantBuilder
{
public:
  PlantBuilder(fig::Shader& shader, Game* game, Barrier& barrier, fig::Terrain* terrain);
  void create() override;
  fig::MenuTextures getPreviewType() override;
};

#endif
