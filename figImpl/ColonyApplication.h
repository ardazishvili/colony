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

#include "ColonyWindow.h"

class ColonyApplication : public Application
{
public:
  ColonyApplication();

  void run() override;

private:
  std::unique_ptr<ColonyWindow> _window;
  Camera _camera;
  std::function<void(std::unique_ptr<Event> event)> _onEvent;
  std::unique_ptr<EventFabric> _eventFabric;

  glm::mat4 _view;
  glm::mat4 _projection;
};

#endif
