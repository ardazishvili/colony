#include <iostream>

#include "../fig/globals.h"
#include "View.h"

float View::VIEW_SCALE = 0.5f;
const float View::R = 4 * M_PI;
const float View::S = 6 * M_PI;

View::View(fig::Shader& shader, glm::vec3 position) :
  _shader(shader), _position(position)
{
}

glm::vec3 View::position() const
{
  if (!fig::flatView) {
    return globeMapper(_position);
  }
  return _position;
}

float View::longitude() const
{
  return _position.x * sqrt(2.0f) / R;
}

float View::latitude() const
{
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

glm::mat4 View::flatModel() const
{
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, position());
  model = glm::rotate(model, glm::radians(_angle), glm::vec3(0, 0, 1));
  model = glm::scale(model, glm::vec3(VIEW_SCALE * _objScale));
  return model;
}

glm::mat4 View::globeModel() const
{
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, position());
  model = glm::rotate(
    model, glm::radians(_angle + 90), glm::vec3(glm::normalize(position())));
  model = glm::rotate(model, longitude(), glm::vec3(0, 0, 1));
  model = glm::rotate(
    model, -latitude() + static_cast<float>(M_PI / 2), glm::vec3(0, 1, 0));
  model = glm::scale(model, glm::vec3(VIEW_SCALE * _objScale));
  return model;
}

glm::vec3 View::globeMapper(glm::vec3 p) const
{
  float longitude = p.x * sqrt(2.0f) / R;
  float latitude = 2 * atan(p.y / (R * (1 + sqrt(2) / 2.0f)));

  return glm::vec3((S + p.z) * cos(latitude) * cos(longitude),
                   (S + p.z) * cos(latitude) * sin(longitude),
                   (S + p.z) * sin(latitude));
}
