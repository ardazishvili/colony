#include <iostream>

#include <GL/glew.h> // Initialize with glewInit()

#include "View.h"

float View::VIEW_SCALE = 0.5f;

View::View(Shader& shader, glm::vec3 position) :
  _shader(shader), _position(position)
{
}
