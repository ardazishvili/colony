#ifndef GUI_LAYER_H
#define GUI_LAYER_H

#include <glm/glm.hpp>

#include "../fig/Layer.h"
#include "../fig/Window.h"

class GuiLayer : public Layer
{
public:
  GuiLayer(const Window::Param& param,
           Window* window,
           glm::mat4& view,
           glm::mat4& projection);
  void init() override;
  void update() override;
  void render() override;

private:
  void showDebug();

  Window::Param _wParam;
  Window* _window;
  glm::mat4& _view;
  glm::mat4& _projection;
};

#endif
