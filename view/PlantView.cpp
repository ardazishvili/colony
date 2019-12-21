#include "PlantView.h"
#include "../engine/Model.h"
#include "../globals.h"

PlantView::PlantView(Shader& shader, glm::vec3 position) :
  AbstractPlantView(shader, position)
{
  _model = modelLoader->models()[Models::Plant];
}

void PlantView::draw()
{
  _scaleFactor = 0.01;
  AbstractPlantView::draw();
}
