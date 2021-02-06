#ifndef SHELL_H
#define SHELL_H

#include <map>

#include <glm/glm.hpp>

#include "../view/ShellView.h"

class Shell
{
public:
  enum class Size { Small, Medium, Big };

  Shell() = delete;
  Shell(fig::Shader& shader, glm::vec3 position, float angle, float distance, Size size = Size::Small);
  ~Shell();
  void update();
  bool isDone();
  static const std::map<Size, int> SHELL_DAMAGE_MAP;

private:
  ShellView _view;
  float _speed;
  float _angle;
  float _distance;
  bool _done{ false };
  Size _size;
};

#endif
