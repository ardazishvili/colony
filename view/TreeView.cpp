#include "TreeView.h"
#include "../globals.h"

TreeView::TreeView(Shader& shader, glm::vec3 position) :
  AbstractPlantView(shader, position)
{
  _model = modelLoader->models()[Models::Tree];
}

void TreeView::draw()
{
  _scaleFactor = 0.03;
  AbstractPlantView::draw();
}
