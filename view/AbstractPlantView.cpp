#include "AbstractPlantView.h"
#include "../globals.h"

AbstractPlantView::AbstractPlantView(Shader& shader, glm::vec3 position) :
  View(shader, position)
{
}

void AbstractPlantView::draw()
{
  _shader.use();
  _shader.configure();
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  if (!flatView) {
    model = globeModel();
  } else {
    model = flatModel();
  }
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->render();
}
