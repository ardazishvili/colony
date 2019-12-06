#ifndef BUILDABLE_STRUCTURE_H
#define BUILDABLE_STRUCTURE_H

#include "Buildable.h"

enum class BuildStage
{
  SetPosition,
  SetAngle,
  Done
};

class BuildableStructure : public Buildable
{
public:
  virtual void setPosition(glm::vec3 position) = 0;
  virtual void setAngle(float angle) = 0;
  virtual void commit() = 0;

protected:
  BuildStage _stage{ BuildStage::SetPosition };
};

#endif
