#include "PlantView.h"
#include "../fig/Model.h"
#include "../fig/globals.h"

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
