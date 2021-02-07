#ifndef SHELL_VIEW_H
#define SHELL_VIEW_H

#include "../fig/Model.h"
#include "../fig/shader/Shader.h"

#include "View.h"

class ShellView : public View
{
public:
  ShellView(glm::vec3 position);
  void draw() override;
  void move(glm::vec2 moveIncrement);
};

#endif
