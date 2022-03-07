#include "view/TreeView.h"

#include "fig/globals.h"

TreeView::TreeView(glm::vec3 position) : AbstractPlantView(position) {
  _model = fig::modelLoader->getModel(fig::ModelType::Tree);
  _objScale = 0.03;
}

void TreeView::draw() { AbstractPlantView::draw(); }
