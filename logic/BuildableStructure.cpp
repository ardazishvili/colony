#include "BuildableStructure.h"

BuildableStructure::BuildableStructure(Shader& textureShader,
                                       Shader& linesShader,
                                       std::unique_ptr<StructureView> view) :
  Buildable(textureShader, linesShader),
  _view(std::move(view))
{
  _viewPtr = _view.get();
}

bool BuildableStructure::isUnderCursor(const glm::vec3& mousePoint)
{
  return _view->contain(mousePoint);
}

void BuildableStructure::commit()
{
  _stage = BuildStage::Done;
  deselect();
}

void BuildableStructure::setAngle(float angle)
{
  _view->rotate(angle);
}

void BuildableStructure::setPosition(glm::vec3 position)
{
  _view->move(position);
}
