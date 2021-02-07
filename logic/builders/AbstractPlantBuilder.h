#ifndef ABSTRACT_PLANT_BUILDER_H
#define ABSTRACT_PLANT_BUILDER_H

#include "../structures/Barrier.h"
#include "AbstractUnitBuilder.h"

class AbstractPlantBuilder : public AbstractUnitBuilder
{
public:
  AbstractPlantBuilder(Game* game, Barrier& barrier, fig::Terrain* terrain);
  glm::vec2 generateUniformPosition() const;

protected:
  Game* _game;
  Barrier& _barrier;
  fig::Terrain* _terrain;
};

#endif
