#include "ColonyApplication.h"
#include "ColonyGameLayer.h"
#include "ColonyGuiLayer.h"
#include "events/ColonyEventFabric.h"

using namespace std::placeholders;

template<typename T>
ColonyApplication<T>::ColonyApplication() :
  _camera(glm::vec3(0.0f, -45.0f, 60.0f),
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f))
{
  _eventFabric = std::make_unique<ColonyEventFabric>();
  int screenWidth = 1920;
  int screenHeight = 1200 - 150;

  fig::Window::Param param = { screenWidth, screenHeight };
  this->_window = std::make_unique<fig::GlfwWindow>(
    _view, _projection, _eventFabric.get(), param);

  _view = glm::lookAt(_camera.eye(), _camera.reference(), _camera.up());
  _projection =
    glm::perspective(glm::radians(_camera.fov()),
                     this->_window->width() / this->_window->height(),
                     0.01f,
                     1000.0f);
  _light = std::make_unique<fig::Light>(
    glm::vec3(1.2f, 0.0f, 5.0f), _camera, _view, _projection);

  auto gameLayer = std::make_unique<ColonyGameLayer>(
    this->_window.get(), &_camera, _light.get(), _view, _projection);
  gameLayer->init();
  this->_window->setOnEvent(gameLayer->onEvent());
  this->addLayer(std::move(gameLayer));

  auto guiLayer = std::make_unique<ColonyGuiLayer>(
    param, this->_window.get(), &_camera, _light.get(), _view, _projection);
  guiLayer->init();
  this->addLayer(std::move(guiLayer));
}

template<typename T>
void ColonyApplication<T>::run()
{
  while (!this->_window->shouldClose()) {
    this->_window->update();

    this->update();
    this->render();
    this->_window->show();
  }
}

template class ColonyApplication<SpdBackend>;
