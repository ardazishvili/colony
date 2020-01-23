#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "../logic/EventManager.h"
#include "../logic/Game.h"
#include "Camera.h"
#include "Light.h"
#include "LinesShader.h"
#include "PhongShader.h"
#include "Skybox.h"
#include "SkyboxShader.h"
#include "Window.h"

class Application
{
public:
  Application();
  Application(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(const Application&) = delete;
  Application& operator=(Application&&) = delete;
  ~Application();

  void run();

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

  std::unique_ptr<Window> _window;
  Camera _camera;
  std::unique_ptr<Terrain> _terrain;

  glm::mat4 _view;
  glm::mat4 _projection;
};

#endif
