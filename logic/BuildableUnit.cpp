#include "BuildableUnit.h"
#include "../globals.h"

BuildableUnit::BuildableUnit(Shader& textureShader,
                             Shader& linesShader,
                             AStar* router) :
  Buildable(textureShader, linesShader),
  _router(router)
{
}

/* bool BuildableUnit::isUnderCursor(const glm::vec3& mousePoint) */
/* { */
/*   return _viewPtr->contain(mousePoint); */
/* } */

void BuildableUnit::render()
{
  Buildable::render();
  if (_path != nullptr) {
    _path->render();
  }
}
