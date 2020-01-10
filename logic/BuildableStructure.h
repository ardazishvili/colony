#ifndef BUILDABLE_STRUCTURE_H
#define BUILDABLE_STRUCTURE_H

#include "../view/StructureView.h"
#include "Buildable.h"
#include "Selectable.h"

enum class BuildStage { SetPosition, SetAngle, Done };

template<typename T>
class Structure
{
public:
  Structure(StructureView* view);
  virtual void commit();
  void setAngle(float angle);
  void setPosition(glm::vec3 position);
  void render();

protected:
  BuildStage _stage{ BuildStage::SetPosition };
  StructureView* _view;
};

#endif
