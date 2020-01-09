#include "TreeView.h"
#include "../globals.h"

TreeView::TreeView(Shader& shader, glm::vec3 position) :
  AbstractPlantView(shader, position)
{
  _model = modelLoader->models()[Models::Tree];
  _objScale = 0.03;
}

void TreeView::draw()
{
  AbstractPlantView::draw();
}
