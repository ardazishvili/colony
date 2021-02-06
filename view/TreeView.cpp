#include "../fig/globals.h"

#include "TreeView.h"

TreeView::TreeView(fig::Shader& shader, glm::vec3 position) : AbstractPlantView(shader, position)
{
  _model = fig::modelLoader->models()[fig::Models::Tree];
  _objScale = 0.03;
}

void TreeView::draw()
{
  AbstractPlantView::draw();
}
