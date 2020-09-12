#ifndef COLONY_APPLICATION_H
#define COLONY_APPLICATION_H

#include <memory>

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "../fig/Application.h"
#include "../fig/Camera.h"
#include "../fig/Light.h"
#include "../fig/LinesShader.h"
#include "../fig/PhongShader.h"
#include "../fig/Skybox.h"
#include "../fig/SkyboxShader.h"
#include "../fig/events/Event.h"
#include "../fig/events/EventFabric.h"

#include "../logic/Game.h"
#include "ColonyEventManager.h"

template<typename T>
class ColonyApplication : public fig::Application<T>
{
public:
  ColonyApplication();

  void run() override;
  void tick() override{};

private:
  fig::Camera _camera;
  std::unique_ptr<fig::Light> _light;
  std::function<void(std::unique_ptr<fig::Event> event)> _onEvent;
  std::unique_ptr<fig::EventFabric> _eventFabric;

  glm::mat4 _view;
  glm::mat4 _projection;
};

#endif
