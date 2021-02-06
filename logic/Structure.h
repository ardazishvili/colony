#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Buildable.h"
#include "Selectable.h"

#include "../view/StructureView.h"

enum class BuildStage { SetPosition, SetAngle, Done };

template<typename T>
class Structure
{
public:
  Structure(StructureView* view);
  virtual ~Structure() = default;
  Structure(const Structure&) = delete;
  Structure(Structure&&) = delete;
  Structure& operator=(const Structure&) = delete;
  Structure& operator=(Structure&&) = delete;

  virtual void commit();
  void setAngle(float angle);
  void setPosition(glm::vec3 position);
  void render();

protected:
  BuildStage _stage{ BuildStage::SetPosition };
  StructureView* _view;
};

#endif
