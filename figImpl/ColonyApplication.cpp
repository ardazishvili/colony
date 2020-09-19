#include "ColonyApplication.h"
#include "ColonyGameLayer.h"
#include "ColonyGuiLayer.h"
#include "events/ColonyEventFabric.h"
#include <glm/fwd.hpp>
#include <memory>

using namespace std::placeholders;

template<typename T>
ColonyApplication<T>::ColonyApplication()
{
  _eventFabric = std::make_unique<ColonyEventFabric>();
  int screenWidth = 1920;
  int screenHeight = 1200 - 150;
  auto camera = std::make_unique<fig::Camera>(glm::vec3(0.0f, -45.0f, 60.0f),
                                              glm::vec3(0.0f, 0.0f, 0.0f),
                                              glm::vec3(0.0f, 0.0f, 1.0f));
  std::vector<std::unique_ptr<fig::Camera>> cameras;
  cameras.push_back(std::move(camera));

  fig::Window::Param param = { screenWidth, screenHeight };
  std::vector<glm::vec3> lightsCoords = { glm::vec3(1.2f, 0.0f, 5.0f) };
  this->_appEnv = std::make_unique<fig::AppEnvPrivate>(
    std::make_unique<fig::GlfwWindow>(_eventFabric.get(), param),
    std::move(cameras),
    lightsCoords);

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
