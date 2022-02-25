#include "logic/Shell.h"

#include <optional>
#include <tuple>

std::map<Shell::Size, float> shellSizeMap = {{Shell::Size::Small, 2.0f},
                                             {Shell::Size::Medium, 3.0f},
                                             {Shell::Size::Big, 4.0f}};

const std::map<Shell::Size, int> Shell::SHELL_DAMAGE_MAP = {
    {Shell::Size::Small, 2},
    {Shell::Size::Medium, 4},
    {Shell::Size::Big, 6},
};

Shell::Shell(glm::vec3 position, float angle, float distance, Size size)
    : _view(position), _angle(angle), _distance(distance), _size(size) {
  _speed = 0.35f;
}

Shell::~Shell() {}

std::optional<std::tuple<float, float, float>> Shell::update() {
  float x = _speed * ::sin(_angle);
  float y = -_speed * ::cos(_angle);
  float distance = ::sqrt(::pow(x, 2) + ::pow(y, 2));
  if (_distance - distance <= 0) {
    _done = true;
    return std::nullopt;
  }
  return std::make_tuple(x, y, distance);
}

void Shell::render() {
  auto update_value = update();
  if (!update_value.has_value()) {
    return;
  }
  auto [x, y, distance] = update_value.value();
  _distance -= distance;
  _view.move(glm::vec2(x, y));
  _view.draw();
}

bool Shell::isDone() { return _done; }
