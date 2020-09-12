#include "ColonyGameLayer.h"

#include "../fig/Light.h"
#include "../fig/globals.h"
#include "../figImpl/ColonyEventManager.h"

ColonyGameLayer::ColonyGameLayer(fig::Window* w,
                                 fig::Camera* c,
                                 fig::Light* l,
                                 glm::mat4& view,
                                 glm::mat4& projection) :
  _window(w),
  _camera(c), _light(l), _view(view), _projection(projection)
{
}

void ColonyGameLayer::init()
{
  _colorShader = std::make_unique<fig::PhongShader>(
    _light,
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_color.vs",
    "/home/roman/repos/colony/shaders/fragment_color.fs");
  _colorNonFlatShader = std::make_unique<fig::PhongShader>(
    _light,
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_color_nonflat.vs",
    "/home/roman/repos/colony/shaders/fragment_color_nonflat.fs");
  _textureShader = std::make_unique<fig::PhongShader>(
    _light,
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_objects.vs",
    "/home/roman/repos/colony/shaders/fragment_objects.fs");
  _lampShader = std::make_unique<fig::PhongShader>(
    _light,
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_light.vs",
    "/home/roman/repos/colony/shaders/fragment_light.fs");
  _light->setShader(_lampShader.get());
  _skyboxShader = std::make_unique<fig::SkyboxShader>(
    _light,
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_skybox.vs",
    "/home/roman/repos/colony/shaders/fragment_skybox.fs");
  _linesShader = std::make_unique<fig::LinesShader>(
    _light,
    *_camera,
    _view,
    _projection,
    "/home/roman/repos/colony/shaders/vertex_lines.vs",
    "/home/roman/repos/colony/shaders/fragment_lines.fs");
  fig::modelLoader = std::make_unique<fig::ModelLoader>(*_textureShader);
  fig::modelLoader->load();

  auto xScale = 2.85f;
  auto yScale = 2.15f;
  auto zScale = 2.0f;
  _terrain = std::make_unique<fig::Terrain>(*_colorShader,
                                            *_camera,
                                            -10.0f * xScale,
                                            -10.0f * yScale,
                                            10.0f * xScale,
                                            10.0f * yScale,
                                            256 / 2,
                                            zScale);
  _game = std::make_unique<Game>(_view, _projection);
  _game->addTerrain(_terrain.get());
  auto mapObstacles = fig::makeObstaclesSegment(
    *_colorNonFlatShader,
    _terrain.get(),
    glm::vec2(-10 * xScale + 0.01, -10 * yScale + 0.01),
    glm::vec2(10 * xScale - 0.01, 10 * yScale - 0.01));
  _astar = std::make_unique<fig::AStar>(mapObstacles->vertices(),
                                        mapObstacles->obstacles(),
                                        mapObstacles->dimensions());
  // TODO downcast
  _eventManager = std::make_shared<ColonyEventManager>(_view,
                                                       _projection,
                                                       _window,
                                                       _game.get(),
                                                       *_camera,
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

  _skybox = std::make_unique<fig::Skybox>(*_skyboxShader);
}

void ColonyGameLayer::update()
{
}

void ColonyGameLayer::render()
{
  _camera->updateSpeed();
  _view = glm::lookAt(_camera->eye(), _camera->reference(), _camera->up());
  _projection = glm::perspective(glm::radians(_camera->fov()),
                                 _window->width() / _window->height(),
                                 0.01f,
                                 1000.0f);

  _terrain.get()->render();
  _eventManager->tick();
  _skybox.get()->render();
  /* auto s = Sphere(colorShader, glm::vec3(0.0f, 0.0f, 5.0f), 1.0f, 50); */
  /* s.render(); */
  _terrain.get()->renderSub();
}

std::function<void(std::unique_ptr<fig::Event> event)>
ColonyGameLayer::onEvent()
{
  return [this](std::unique_ptr<fig::Event> event) {
    event->process(_camera, _eventManager.get());
  };
}
