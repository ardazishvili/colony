#ifndef COLONY_GUI_LAYER_H
#define COLONY_GUI_LAYER_H

#include <glm/glm.hpp>

#include "../fig/Application.h"
#include "../fig/GuiLayer.h"
#include "../fig/ImGuiBackend.h"
#include "../fig/Window.h"

class ColonyGuiLayer : public fig::GuiLayer
{
public:
  ColonyGuiLayer(const fig::AppEnv& env) :
    GuiLayer(env.window, std::make_unique<fig::ImGuiBackend>()),
    _camera(env.camera), _light(env.light), _view(env.view),
    _projection(env.projection)
  {
    init();
  }
  ~ColonyGuiLayer();
  void init() override;
  void update() override;
  void render() override;

private:
  void showDebug();

  fig::Camera* _camera;
  fig::Light* _light;
  glm::mat4& _view;
  glm::mat4& _projection;
};

#endif
