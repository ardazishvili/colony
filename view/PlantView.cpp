#include "view/PlantView.h"

#include "fig/Model.h"
#include "fig/globals.h"

PlantView::PlantView(glm::vec3 position) : AbstractPlantView(position) {
  _model = fig::modelLoader->getModel(fig::ModelType::Plant);
  _objScale = 0.01;
}

void PlantView::draw() { AbstractPlantView::draw(); }
