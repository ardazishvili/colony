#include "PlantView.h"
#include "../engine/Model.h"
#include "../globals.h"

PlantView::PlantView(Shader& shader, glm::vec3 position) :
  AbstractPlantView(shader, position)
{
  _model = modelLoader->models()[Models::Plant];
  _objScale = 0.01;
}

void PlantView::draw()
{
  AbstractPlantView::draw();
}
