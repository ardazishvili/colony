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
#include "../logic/EventManager.h"
#include "../logic/Game.h"

#include "ColonyWindow.h"

class ColonyApplication : public Application
{
public:
  ColonyApplication();

  void run() override;

private:
  std::unique_ptr<Light> _light;
  std::unique_ptr<EventManager> _eventManager;
  std::unique_ptr<Skybox> _skybox;
  std::unique_ptr<Game> _game;
  std::unique_ptr<PhongShader> _colorShader;
  std::unique_ptr<PhongShader> _colorNonFlatShader;
  std::unique_ptr<PhongShader> _lampShader;
  std::unique_ptr<PhongShader> _textureShader;
  std::unique_ptr<LinesShader> _linesShader;
  std::unique_ptr<SkyboxShader> _skyboxShader;
  std::unique_ptr<AStar> _astar;

  std::unique_ptr<ColonyWindow> _window;
  Camera _camera;
  std::unique_ptr<Terrain> _terrain;
  std::function<void(std::unique_ptr<Event> event)> _onEvent;
  std::unique_ptr<EventFabric> _eventFabric;

  glm::mat4 _view;
  glm::mat4 _projection;
};

#endif
