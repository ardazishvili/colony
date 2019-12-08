#include "BarrierView.h"
#include "../globals.h"

BarrierView::BarrierView(Shader& shader, glm::vec3 position) :
  _shader(shader), _position(position)
{
  _model = modelLoader->models()[Models::Barrier];
}

void BarrierView::draw()
{
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  _shader.setBool("animated", false);
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::scale(model, glm::vec3(_scaleFactor));
  _shader.setTransformation("model", glm::value_ptr(model));
  _model->render();
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
}
