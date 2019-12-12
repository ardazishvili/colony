#include "PlantView.h"
#include "../globals.h"

PlantView::PlantView(Shader& shader, glm::vec3 position) :
  View(shader, position)
{
  _model = modelLoader->models()[Models::Plant];
}

void PlantView::draw()
{
  _scaleFactor = 0.01;
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::scale(model, glm::vec3(_scaleFactor));
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->render();
}
