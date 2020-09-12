#ifndef COLONY_GUI_LAYER_H
#define COLONY_GUI_LAYER_H

#include <glm/glm.hpp>

#include "../fig/GuiLayer.h"
#include "../fig/Window.h"

class ColonyGuiLayer : public fig::GuiLayer
{
public:
  ColonyGuiLayer(const fig::Window::Param& param,
                 fig::Window* window,
                 glm::mat4& view,
                 glm::mat4& projection);
  ~ColonyGuiLayer();
  void init() override;
  void update() override;
  void render() override;

private:
  void showDebug();

  fig::Window::Param _wParam;
  glm::mat4& _view;
  glm::mat4& _projection;
};

#endif
