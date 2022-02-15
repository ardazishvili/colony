#pragma once

#include <glm/glm.hpp>
#include <map>
#include <optional>

#include "view/ShellView.h"

class Shell {
 public:
  enum class Size { Small, Medium, Big };

  Shell() = delete;
  Shell(glm::vec3 position, float angle, float distance,
        Size size = Size::Small);
  ~Shell();
  void render();
  bool isDone();
  static const std::map<Size, int> SHELL_DAMAGE_MAP;

 private:
  std::optional<std::tuple<float, float, float>> update();

  ShellView _view;
  float _speed;
  float _angle;
  float _distance;
  bool _done{false};
  Size _size;
};
