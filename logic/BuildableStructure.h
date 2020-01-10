#ifndef BUILDABLE_STRUCTURE_H
#define BUILDABLE_STRUCTURE_H

#include "../view/StructureView.h"
#include "Buildable.h"
#include "Selectable.h"

enum class BuildStage { SetPosition, SetAngle, Done };

class BuildableStructure
  : public Buildable
  , public Selectable<BuildableStructure>
{
public:
  BuildableStructure(Shader& textureShader,
                     Shader& linesShader,
                     std::unique_ptr<StructureView> view);
  /* bool isUnderCursor(const glm::vec3& mousePoint); */
  virtual void commit();
  void setAngle(float angle);
  void setPosition(glm::vec3 position);

protected:
  friend Selectable;

  BuildStage _stage{ BuildStage::SetPosition };
  std::unique_ptr<StructureView> _view;
};

#endif
