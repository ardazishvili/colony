#ifndef ABSTRACT_PLANT_BUILDER_H
#define ABSTRACT_PLANT_BUILDER_H

#include "AbstractUnitBuilder.h"
#include "Barrier.h"

class AbstractPlantBuilder : public AbstractUnitBuilder
{
public:
  AbstractPlantBuilder(Shader& shader,
                       Game* game,
                       Barrier& barrier,
                       Terrain* terrain);
  glm::vec2 generateUniformPosition() const;

protected:
  Shader& _shader;
  Game* _game;
  Barrier& _barrier;
  Terrain* _terrain;
};

#endif
