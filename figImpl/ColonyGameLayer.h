#ifndef COLONY_GAME_LAYER_H
#define COLONY_GAME_LAYER_H

#include <memory>

#include "../fig/Application.h"
#include "../fig/EventManager.h"
#include "../fig/GameLayer.h"
#include "../fig/Skybox.h"
#include "../fig/Terrain.h"
#include "../fig/shader/LinesShader.h"
#include "../fig/shader/PhongShader.h"
#include "../fig/shader/SkyboxShader.h"

#include "../logic/Game.h"

class Window;
class Camera;
class ColonyGameLayer : public fig::GameLayer
{
public:
  ColonyGameLayer(const fig::AppEnv& env) :
    _window(env.window), _camera(env.camera), _light(env.light), _view(env.view), _projection(env.projection)
  {
    init();
  }
  void init() override;
  void update() override;
  void render() override;

  std::function<void(std::unique_ptr<fig::Event> event)> onEvent();

private:
  std::unique_ptr<fig::PhongShader> _lampShader;
  std::unique_ptr<fig::PhongShader> _colorShader;
  std::unique_ptr<fig::PhongShader> _colorNonFlatShader;
  std::unique_ptr<fig::PhongShader> _textureShader;
  std::unique_ptr<fig::LinesShader> _linesShader;
  std::unique_ptr<fig::SkyboxShader> _skyboxShader;
  std::unique_ptr<fig::AStar> _astar;

  fig::Window* _window;
  fig::Camera* _camera;
  fig::Light* _light;
  std::shared_ptr<fig::EventManager> _eventManager;
  std::unique_ptr<fig::Terrain> _terrain;
  std::unique_ptr<fig::Skybox> _skybox;
  std::unique_ptr<Game> _game;

  glm::mat4& _view;
  glm::mat4& _projection;

  std::function<void(std::unique_ptr<fig::Event> event)> _onEvent;
};

#endif
