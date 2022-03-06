#include "figImpl/ColonyApplication.h"

#include "fig/Camera.h"
#include "fig/GlfwWindow.h"
#include "fig/Light.h"
#include "figImpl/ColonyGameLayer.h"
#include "figImpl/ColonyGuiLayer.h"
#include "figImpl/events/ColonyEventFabric.h"

template <typename T>
ColonyApplication<T>::ColonyApplication() {
  std::vector<std::unique_ptr<fig::Camera>> cameras;
  cameras.push_back(std::make_unique<fig::Camera>(
      glm::vec3(0.0f, -45.0f, 60.0f), glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 1.0f)));

  auto config = CONFIG.get();
  fig::Window::Param param = {config.window_width, config.window_height};
  std::vector<glm::vec3> lightsCoords = {glm::vec3(1.2f, 0.0f, 5.0f)};

  _eventFabric = std::make_unique<ColonyEventFabric>();
  this->_appEnv = std::make_unique<fig::AppEnvPrivate>(
      std::make_unique<fig::GlfwWindow>(_eventFabric.get(), param),
      std::move(cameras), lightsCoords);

  auto env = this->getEnv();
  auto gameLayer = std::make_unique<ColonyGameLayer>(env);
  this->_appEnv.get()->window->setOnEvent(gameLayer->onEvent());
  this->addLayer(std::move(gameLayer));
  this->addLayer(std::make_unique<ColonyGuiLayer>(env));
}

template <typename T>
void ColonyApplication<T>::run() {
  while (!this->_appEnv.get()->window->shouldClose()) {
    this->_appEnv.get()->window->update();

    this->update();
    this->render();
    this->_appEnv.get()->window->show();
  }
}

template class ColonyApplication<SpdBackend>;
