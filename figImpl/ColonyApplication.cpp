#include "ColonyApplication.h"
#include "ColonyGameLayer.h"
#include "ColonyGuiLayer.h"
#include "events/ColonyEventFabric.h"
#include <memory>

using namespace std::placeholders;

template<typename T>
ColonyApplication<T>::ColonyApplication()
{
  _eventFabric = std::make_unique<ColonyEventFabric>();
  int screenWidth = 1920;
  int screenHeight = 1200 - 150;

  fig::Window::Param param = { screenWidth, screenHeight };
  this->_appEnv = std::make_unique<fig::AppEnvPrivate>(
    std::make_unique<fig::GlfwWindow>(_eventFabric.get(), param));

  auto env = this->getEnv();
  auto gameLayer = std::make_unique<ColonyGameLayer>(env);
  this->_appEnv.get()->window->setOnEvent(gameLayer->onEvent());
  this->addLayer(std::move(gameLayer));

  auto guiLayer = std::make_unique<ColonyGuiLayer>(env);
  this->addLayer(std::move(guiLayer));
}

template<typename T>
void ColonyApplication<T>::run()
{
  while (!this->_appEnv.get()->window->shouldClose()) {
    this->_appEnv.get()->window->update();

    this->update();
    this->render();
    this->_appEnv.get()->window->show();
  }
}

template class ColonyApplication<SpdBackend>;
