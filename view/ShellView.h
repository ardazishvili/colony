#ifndef SHELL_VIEW_H
#define SHELL_VIEW_H

#include "../engine/Model.h"
#include "../engine/Shader.h"
#include "View.h"
#include <GL/glew.h>

class ShellView : public View
{
public:
  ShellView(Shader& shader, glm::vec3 position);
  void draw() override;
  glm::vec3 position() const override;
  void move(glm::vec2 moveIncrement);

private:
  /* std::shared_ptr<Model> _model; */
  /* Shader& _shader; */
  /* glm::vec3 _position; */
};

#endif
