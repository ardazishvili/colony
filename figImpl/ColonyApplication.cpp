#include "ColonyApplication.h"
#include "ColonyGameLayer.h"
#include "ColonyGuiLayer.h"
#include "events/ColonyEventFabric.h"

ColonyApplication::ColonyApplication() :
  _camera(glm::vec3(0.0f, -45.0f, 60.0f),
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f))
{
  _eventFabric = std::make_unique<ColonyEventFabric>();
  int screenWidth = 1920;
  int screenHeight = 1200 - 150;
  Window::Param param = { screenWidth, screenHeight };
  _window =
    std::make_unique<GlfwWindow>(_view, _projection, _eventFabric.get(), param);

  auto gameLayer = std::make_unique<ColonyGameLayer>(
    _window.get(), &_camera, _view, _projection);
  gameLayer->init();
  _window->setOnEvent(gameLayer->onEvent());
  addLayer(std::move(gameLayer));

  auto guiLayer =
    std::make_unique<ColonyGuiLayer>(param, _window.get(), _view, _projection);
  guiLayer->init();
  addLayer(std::move(guiLayer));
}

void ColonyApplication::run()
{
  while (!_window->shouldClose()) {
    _window->update();

    update();
    render();
    _window->show();
  }
}

