#include "Plant.h"

Plant::Plant(Shader& shader, glm::vec3 position) : _view(shader, position) {}

void Plant::render()
{
  _view.draw();
}

glm::vec2 Plant::position()
{
  return _view.position();
}
