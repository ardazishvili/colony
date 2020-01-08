#include <iostream>

#include <GL/glew.h> // Initialize with glewInit()

#include "../globals.h"
#include "View.h"

float View::VIEW_SCALE = 0.5f;

View::View(Shader& shader, glm::vec3 position) :
  _shader(shader), _position(position)
{
}

glm::vec3 View::position() const
{
  if (!flatView) {
    float R = 4.0 * 3.1415;
    float S = 6.0 * 3.1415;
    float longitude = _position.x * sqrt(2.0f) / R;
    float latitude = 2 * atan(_position.y / (R * (1 + sqrt(2) / 2.0f)));

    return glm::vec3((S + _position.z) * cos(latitude) * cos(longitude),
                     (S + _position.z) * cos(latitude) * sin(longitude),
                     (S + _position.z) * sin(latitude));
  }
  return _position;
}

float View::longitude() const
{
  float R = 4.0 * 3.1415;
  return _position.x * sqrt(2.0f) / R;
}

float View::latitude() const
{
  float R = 4.0 * 3.1415;
  return 2 * atan(_position.y / (R * (1 + sqrt(2) / 2.0f)));
}

float View::h(float phi) const
{
  return (1 + (::sqrt(2) / 2.0)) * (0.5 / ::pow(::cos(phi / 2.0), 2));
}

float View::k(float phi) const
{
  return 1.0 / (::cos(phi) * ::sqrt(2.0));
}
