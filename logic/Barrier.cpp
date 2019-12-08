#include "Barrier.h"

Barrier::Barrier(Shader& shader, glm::vec3 position) : _view(shader, position)
{}

void Barrier::render()
{
  _view.draw();
}
