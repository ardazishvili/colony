#include "BuildableStructure.h"

BuildableStructure::BuildableStructure(Shader& shader,
                                       std::unique_ptr<StructureView> view) :
  Buildable(shader),
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
