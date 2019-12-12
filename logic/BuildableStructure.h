#ifndef BUILDABLE_STRUCTURE_H
#define BUILDABLE_STRUCTURE_H

#include "../view/StructureView.h"
#include "Buildable.h"

enum class BuildStage { SetPosition, SetAngle, Done };

class BuildableStructure : public Buildable
{
public:
  BuildableStructure(Shader& shader, std::unique_ptr<StructureView> view);
  bool isUnderCursor(const glm::vec3& mousePoint);
  virtual void setPosition(glm::vec3 position) = 0;
  virtual void setAngle(float angle) = 0;
  virtual void commit() = 0;

protected:
  BuildStage _stage{ BuildStage::SetPosition };
  std::unique_ptr<StructureView> _view;
};

#endif
