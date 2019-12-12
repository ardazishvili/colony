#include "BuildableUnit.h"

BuildableUnit::BuildableUnit(Shader& shader, std::unique_ptr<UnitView> view) :
  Buildable(shader), _view(std::move(view))
{
}

bool BuildableUnit::isUnderCursor(const glm::vec3& mousePoint)
{
  return _view->contain(mousePoint);
}
