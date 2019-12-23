#include "BuildableUnit.h"

BuildableUnit::BuildableUnit(Shader& textureShader,
                             Shader& linesShader,
                             std::unique_ptr<UnitView> view) :
  Buildable(textureShader, linesShader),
  _view(std::move(view)), _path(linesShader)
{
  _viewPtr = _view.get();
}

bool BuildableUnit::isUnderCursor(const glm::vec3& mousePoint)
{
  return _view->contain(mousePoint);
}

void BuildableUnit::render()
{
  Buildable::render();
  _path.render();
}
