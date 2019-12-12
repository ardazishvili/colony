#include "ShellView.h"
#include "../globals.h"

ShellView::ShellView(Shader& shader, glm::vec3 position) :
  View(shader, position)
{
  _model = modelLoader->models()[Models::Shell];
}

void ShellView::draw()
{

  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _position);
  model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
  model = glm::scale(model, glm::vec3(VIEW_SCALE));
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);
  _model->render();
}

void ShellView::move(glm::vec2 moveIncrement)
{
  _position.x += moveIncrement.x;
  _position.y += moveIncrement.y;
}
