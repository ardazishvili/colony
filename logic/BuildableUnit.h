#ifndef BUILDABLE_UNIT_H
#define BUILDABLE_UNIT_H

#include "../view/UnitView.h"
#include "Buildable.h"

class BuildableUnit : public Buildable
{
public:
  BuildableUnit(Shader& shader, std::unique_ptr<UnitView> view);
  bool isUnderCursor(const glm::vec3& mousePoint);
  virtual void startShooting(Buildable* other) = 0;
  virtual void startMoving(glm::vec3 endPoint) = 0;

protected:
  std::unique_ptr<UnitView> _view;
};

#endif
