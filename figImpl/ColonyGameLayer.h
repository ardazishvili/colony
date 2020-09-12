#ifndef COLONY_GAME_LAYER_H
#define COLONY_GAME_LAYER_H

#include <memory>

#include "../fig/Camera.h"
#include "../fig/EventManager.h"
#include "../fig/GameLayer.h"
#include "../fig/GlfwWindow.h"
#include "../fig/LinesShader.h"
#include "../fig/PhongShader.h"
#include "../fig/Skybox.h"
#include "../fig/SkyboxShader.h"
#include "../fig/Terrain.h"

#include "../logic/Game.h"

class Window;
class EventManager;
class ColonyGameLayer : public fig::GameLayer
{
public:
  ColonyGameLayer(fig::Window* w,
                  fig::Camera* c,
                  fig::Light* l,
                  glm::mat4& view,
                  glm::mat4& projection);
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
