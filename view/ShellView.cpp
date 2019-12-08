#include "ShellView.h"
#include "../globals.h"

ShellView::ShellView(Shader& shader, glm::vec3 position) :
  _shader(shader), _position(position)
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

glm::vec3 ShellView::position()
{
  return glm::vec3(_position.x, _position.y, _position.z);
}

void ShellView::move(glm::vec2 moveIncrement)
{
  _position.x += moveIncrement.x;
  _position.y += moveIncrement.y;
}
