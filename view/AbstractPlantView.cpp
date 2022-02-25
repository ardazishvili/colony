#include "view/AbstractPlantView.h"

#include "fig/globals.h"
#include "figImpl/globals.h"

AbstractPlantView::AbstractPlantView(glm::vec3 position) : View(position) {}

void AbstractPlantView::draw() {
  _shader.use();
  _shader.configure();
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  model = flatView ? flatModel() : globeModel();
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->render();
}
