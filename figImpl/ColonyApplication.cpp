#include <cstdio>
#include <functional>

#include "../fig/imgui/imgui.h"
#include "../fig/imgui/imgui_impl_glfw.h"
#include "../fig/imgui/imgui_impl_opengl3.h"

#include "../fig/globals.h"
#include "ColonyApplication.h"
#include "GameLayer.h"
#include "events/ColonyEventFabric.h"

using namespace std::placeholders;

ColonyApplication::ColonyApplication() :
  _camera(glm::vec3(0.0f, -45.0f, 60.0f),
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f))
{
  _onEvent = [this](std::unique_ptr<Event> event) {
    event->process(&_camera, _eventManager);
  };
  _eventFabric = std::make_unique<ColonyEventFabric>();
  _window =
    std::make_unique<ColonyWindow>(_view, _projection, _eventFabric.get());
  /* _view = glm::lookAt(_camera.eye(), _camera.reference(), _camera.up()); */
  /* _projection = glm::perspective(glm::radians(_camera.fov()), */
  /*                                _window->width() / _window->height(), */
  /*                                0.01f, */
  /*                                1000.0f); */

  /* _light = std::make_unique<Light>( */
  /*   glm::vec3(1.2f, 0.0f, 5.0f), _camera, _view, _projection); */
  /* _colorShader = std::make_unique<PhongShader>( */
  /*   _light.get(), */
  /*   _camera, */
  /*   _view, */
  /*   _projection, */
  /*   "/home/roman/repos/colony/shaders/vertex_color.vs", */
  /*   "/home/roman/repos/colony/shaders/fragment_color.fs"); */
  /* _colorNonFlatShader = std::make_unique<PhongShader>( */
  /*   _light.get(), */
  /*   _camera, */
  /*   _view, */
  /*   _projection, */
  /*   "/home/roman/repos/colony/shaders/vertex_color_nonflat.vs", */
  /*   "/home/roman/repos/colony/shaders/fragment_color_nonflat.fs"); */
  /* _textureShader = std::make_unique<PhongShader>( */
  /*   _light.get(), */
  /*   _camera, */
  /*   _view, */
  /*   _projection, */
  /*   "/home/roman/repos/colony/shaders/vertex_objects.vs", */
  /*   "/home/roman/repos/colony/shaders/fragment_objects.fs"); */
  /* _lampShader = std::make_unique<PhongShader>( */
  /*   _light.get(), */
  /*   _camera, */
  /*   _view, */
  /*   _projection, */
  /*   "/home/roman/repos/colony/shaders/vertex_light.vs", */
  /*   "/home/roman/repos/colony/shaders/fragment_light.fs"); */
  /* _light->setShader(_lampShader.get()); */
  /* _skyboxShader = std::make_unique<SkyboxShader>( */
  /*   _light.get(), */
  /*   _camera, */
  /*   _view, */
  /*   _projection, */
  /*   "/home/roman/repos/colony/shaders/vertex_skybox.vs", */
  /*   "/home/roman/repos/colony/shaders/fragment_skybox.fs"); */
  /* _linesShader = std::make_unique<LinesShader>( */
  /*   _light.get(), */
  /*   _camera, */
  /*   _view, */
  /*   _projection, */
  /*   "/home/roman/repos/colony/shaders/vertex_lines.vs", */
  /*   "/home/roman/repos/colony/shaders/fragment_lines.fs"); */
  /* modelLoader = std::make_unique<ModelLoader>(*_textureShader); */
  /* modelLoader->load(); */

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  auto gameLayer =
    std::make_unique<GameLayer>(_window.get(), &_camera, _view, _projection);
  gameLayer->init();
  _window->setOnEvent(gameLayer->onEvent());
  addLayer(std::move(gameLayer));

  /* auto xScale = 2.85f; */
  /* auto yScale = 2.15f; */
  /* auto zScale = 2.0f; */
  /* _terrain = std::make_unique<Terrain>(*_colorShader, */
  /*                                      _camera, */
  /*                                      -10.0f * xScale, */
  /*                                      -10.0f * yScale, */
  /*                                      10.0f * xScale, */
  /*                                      10.0f * yScale, */
  /*                                      256 / 2, */
  /*                                      zScale); */
  /* _game = std::make_unique<Game>(_view, _projection); */
  /* _game->addTerrain(_terrain.get()); */
  /* auto mapObstacles = */
  /*   ::makeObstaclesSegment(*_colorNonFlatShader, */
  /*                          _terrain.get(), */
  /*                          glm::vec2(-10 * xScale + 0.01, -10 * yScale +
   * 0.01), */
  /*                          glm::vec2(10 * xScale - 0.01, 10 * yScale -
   * 0.01)); */
  /* _astar = std::make_unique<AStar>(mapObstacles->vertices(), */
  /*                                  mapObstacles->obstacles(), */
  /*                                  mapObstacles->dimensions()); */
  /* _eventManager = std::make_unique<EventManager>(_view, */
  /*                                                _projection, */
  /*                                                _window.get(), */
  /*                                                _game.get(), */
  /*                                                _camera, */
  /*                                                *_textureShader, */
  /*                                                *_colorShader, */
  /*                                                *_colorNonFlatShader, */
  /*                                                *_linesShader, */
  /*                                                _terrain.get(), */
  /*                                                mapObstacles, */
  /*                                                _astar.get()); */
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  /* createTank(_game.get(), */
  /*            *_textureShader, */
  /*            *_linesShader, */
  /*            _astar.get(), */
  /*            _terrain.get()->getXYZ(glm::vec2(0.0, 0.0f))); */
  /* createTank(_game.get(), */
  /*            *_textureShader, */
  /*            *_linesShader, */
  /*            _astar.get(), */
  /*            _terrain.get()->getXYZ(glm::vec2(5.0, 5.0f))); */
  /* createTank(_game.get(), */
  /*            *_textureShader, */
  /*            *_linesShader, */
  /*            _astar.get(), */
  /*            _terrain.get()->getXYZ(glm::vec2(-5.0, -5.0f))); */
  /* createTank(_game.get(), */
  /*            *_textureShader, */
  /*            *_linesShader, */
  /*            _astar.get(), */
  /*            _terrain.get()->getXYZ(glm::vec2(0.0, 5.0f))); */
  /* createTank(_game.get(), */
  /*            *_textureShader, */
  /*            *_linesShader, */
  /*            _astar.get(), */
  /*            _terrain.get()->getXYZ(glm::vec2(0.0, -5.0f))); */

  /* _skybox = std::make_unique<Skybox>(*_skyboxShader); */
}

void ColonyApplication::run()
{
  while (!glfwWindowShouldClose(_window->_window)) {
    /* _camera.updateSpeed(); */
    _window->preUpdate();

    render();
    /* _view = glm::lookAt(_camera.eye(), _camera.reference(), _camera.up());
     */
    /* _projection = glm::perspective(glm::radians(_camera.fov()), */
    /*                                _window->width() / _window->height(),
     */
    /*                                0.01f, */
    /*                                1000.0f); */

    /* _terrain.get()->render(); */
    /* _eventManager->tick(); */
    /* _skybox.get()->render(); */
    /* auto s = Sphere(colorShader, glm::vec3(0.0f, 0.0f, 5.0f), 1.0f,
       50); */
    /* s.render(); */
    /* _terrain.get()->renderSub(); */
    _window->postUpdate();
  }
}

