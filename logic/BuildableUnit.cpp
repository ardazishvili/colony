#include "BuildableUnit.h"
#include "../globals.h"

BuildableUnit::BuildableUnit(Shader& textureShader,
                             Shader& linesShader,
                             std::unique_ptr<UnitView> view,
                             AStar* router) :
  Buildable(textureShader, linesShader),
  _view(std::move(view)), _path(linesShader, router)
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
  if (_path.isSettedUp()) {
    _path.render();
  }
}
