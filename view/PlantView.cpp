#include "../fig/Model.h"
#include "../fig/globals.h"

#include "PlantView.h"

PlantView::PlantView(glm::vec3 position) : AbstractPlantView(position)
{
  _model = fig::modelLoader->models()[fig::Models::Plant];
  _objScale = 0.01;
}

void PlantView::draw()
{
  AbstractPlantView::draw();
}
