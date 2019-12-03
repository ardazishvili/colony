#ifndef BUILDABLE_UNIT_H
#define BUILDABLE_UNIT_H

#include "Buildable.h"

class BuildableUnit : public Buildable {
public:
  virtual void startShooting(Buildable* other) = 0;
  virtual void startMoving(glm::vec2 endPoint) = 0;
};

#endif
