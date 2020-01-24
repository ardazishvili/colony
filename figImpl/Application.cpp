#include <cstdio>
#include <functional>

#include "../fig/imgui/imgui.h"
#include "../fig/imgui/imgui_impl_glfw.h"
#include "../fig/imgui/imgui_impl_opengl3.h"

#include "../fig/globals.h"
#include "Application.h"
#include "events/ColonyEventFabric.h"

using namespace std::placeholders;

Application::Application() :
  _camera(glm::vec3(0.0f, -45.0f, 60.0f),
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f))
{
  _onEvent = [this](std::unique_ptr<Event> event) {
    event->process(&_camera, _eventManager.get());
  };
  _eventFabric = std::make_unique<ColonyEventFabric>();
  _window =
    std::make_unique<Window>(_view, _projection, _onEvent, _eventFabric.get());
  _view = glm::lookAt(_camera.eye(), _camera.reference(), _camera.up());
  _projection = glm::perspective(glm::radians(_camera.fov()),
                                 _window->width() / _window->height(),
                                 0.01f,
                                 1000.0f);

  _light = std::make_unique<Light>(
    glm::vec3(1.2f, 0.0f, 5.0f), _camera, _view, _projection);
  _colorShader = std::make_unique<PhongShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_color.vs",
    "/home/roman/repos/colony/shaders/fragment_color.fs");
  _colorNonFlatShader = std::make_unique<PhongShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_color_nonflat.vs",
    "/home/roman/repos/colony/shaders/fragment_color_nonflat.fs");
  _textureShader = std::make_unique<PhongShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_objects.vs",
    "/home/roman/repos/colony/shaders/fragment_objects.fs");
  _lampShader = std::make_unique<PhongShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_light.vs",
    "/home/roman/repos/colony/shaders/fragment_light.fs");
  _light->setShader(_lampShader.get());
  _skyboxShader = std::make_unique<SkyboxShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_skybox.vs",
    "/home/roman/repos/colony/shaders/fragment_skybox.fs");
  _linesShader = std::make_unique<LinesShader>(
    _light.get(),
    _camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_lines.vs",
    "/home/roman/repos/colony/shaders/fragment_lines.fs");
  modelLoader = std::make_unique<ModelLoader>(*_textureShader);
  modelLoader->load();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  auto xScale = 2.85f;
  auto yScale = 2.15f;
  auto zScale = 2.0f;
  _terrain = std::make_unique<Terrain>(*_colorShader,
                                       _camera,
                                       -10.0f * xScale,
                                       -10.0f * yScale,
                                       10.0f * xScale,
                                       10.0f * yScale,
                                       256 / 2,
                                       zScale);
  _game = std::make_unique<Game>(_view, _projection);
  _game->addTerrain(_terrain.get());
  auto mapObstacles =
    ::makeObstaclesSegment(*_colorNonFlatShader,
                           _terrain.get(),
                           glm::vec2(-10 * xScale + 0.01, -10 * yScale + 0.01),
                           glm::vec2(10 * xScale - 0.01, 10 * yScale - 0.01));
  _astar = std::make_unique<AStar>(mapObstacles->vertices(),
                                   mapObstacles->obstacles(),
                                   mapObstacles->dimensions());
  _eventManager = std::make_unique<EventManager>(_view,
                                                 _projection,
                                                 _window.get(),
                                                 _game.get(),
                                                 _camera,
                                                 *_textureShader,
                                                 *_colorShader,
                                                 *_colorNonFlatShader,
                                                 *_linesShader,
                                                 _terrain.get(),
                                                 mapObstacles,
                                                 _astar.get());

  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(0.0, 0.0f)));
  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(5.0, 5.0f)));
  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(-5.0, -5.0f)));
  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(0.0, 5.0f)));
  createTank(_game.get(),
             *_textureShader,
             *_linesShader,
             _astar.get(),
             _terrain.get()->getXYZ(glm::vec2(0.0, -5.0f)));

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  _skybox = std::make_unique<Skybox>(*_skyboxShader);
}

void Application::run()
{
  while (!glfwWindowShouldClose(_window->_window)) {
    _camera.updateSpeed();
    _window->preUpdate();

    ImGui::Begin("camera");
    static float camera_z = 60.0f;
    ImGui::SetWindowPos(ImVec2(0, 210));
    ImGui::SetWindowSize(ImVec2(500, 50));
    ImGui::SliderFloat("camera z", &camera_z, -100.0f, 100.0f);
    ImGui::End();
    auto eye = _camera.eye();
    eye.z = camera_z;
    _camera.setEye(eye);

    ImGui::Begin("models scale");
    ImGui::SetWindowPos(ImVec2(0, 450));
    ImGui::SetWindowSize(ImVec2(200, 50));
    ImGui::SliderFloat("scale", &View::VIEW_SCALE, 0.0f, 1.0f);
    ImGui::End();

    ImGui::Begin("light");
    static float x = 1.2;
    static float y = 0.0;
    static float z = 90.0;
    ImGui::SetWindowPos(ImVec2(0, 110));
    ImGui::SetWindowSize(ImVec2(500, 100));
    ImGui::SliderFloat("light x", &x, -10.0f, 10.0f);
    ImGui::SliderFloat("light y", &y, -10.0f, 10.0f);
    ImGui::SliderFloat("light z", &z, -100.0f, 100.0f);
    ImGui::End();
    _light->setPosition(glm::vec3(x, y, z));

    _view = glm::lookAt(_camera.eye(), _camera.reference(), _camera.up());
    _projection = glm::perspective(glm::radians(_camera.fov()),
                                   _window->width() / _window->height(),
                                   0.01f,
                                   1000.0f);

    _terrain.get()->render();
    _eventManager->tick();
    _skybox.get()->render();
    /* auto s = Sphere(colorShader, glm::vec3(0.0f, 0.0f, 5.0f), 1.0f, 50); */
    /* s.render(); */
    _terrain.get()->renderSub();
    _window->postUpdate();
  }
}

Application::~Application()
{
}
