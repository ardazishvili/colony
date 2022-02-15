#pragma once

#include "logic/builders/AbstractUnitBuilder.h"
#include "logic/structures/Barrier.h"

class AbstractPlantBuilder : public AbstractUnitBuilder {
 public:
  AbstractPlantBuilder(Barrier& barrier, fig::Terrain& terrain);
  glm::vec2 generateUniformPosition() const;

 protected:
  Barrier& _barrier;
  fig::Terrain& _terrain;
};
