#include "PlantView.h"
#include "../fig/Model.h"
#include "../fig/globals.h"

PlantView::PlantView(fig::Shader& shader, glm::vec3 position) :
  AbstractPlantView(shader, position)
{
  _model = fig::modelLoader->models()[fig::Models::Plant];
  _objScale = 0.01;
}

void PlantView::draw()
{
  AbstractPlantView::draw();
}
