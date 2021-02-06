#ifndef ABSTRACT_PLANT_BUILDER_H
#define ABSTRACT_PLANT_BUILDER_H

#include "AbstractUnitBuilder.h"
#include "Barrier.h"

class AbstractPlantBuilder : public AbstractUnitBuilder
{
public:
  AbstractPlantBuilder(fig::Shader& shader, Game* game, Barrier& barrier, fig::Terrain* terrain);
  glm::vec2 generateUniformPosition() const;

protected:
  fig::Shader& _shader;
  Game* _game;
  Barrier& _barrier;
  fig::Terrain* _terrain;
};

#endif
