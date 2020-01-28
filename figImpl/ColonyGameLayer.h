#ifndef COLONY_GAME_LAYER_H
#define COLONY_GAME_LAYER_H

#include <memory>

#include "../fig/Camera.h"
#include "../fig/GameLayer.h"
#include "../fig/LinesShader.h"
#include "../fig/PhongShader.h"
#include "../fig/Skybox.h"
#include "../fig/SkyboxShader.h"
#include "../fig/Terrain.h"

#include "../fig/GlfwWindow.h"
#include "../logic/Game.h"

class Window;
class EventManager;
class ColonyGameLayer : public GameLayer
{
public:
  ColonyGameLayer(Window* w, Camera* c, glm::mat4& view, glm::mat4& projection);
  void init() override;
  void update() override;
  void render() override;

  std::function<void(std::unique_ptr<Event> event)> onEvent();

private:
  std::unique_ptr<Light> _light;
  std::unique_ptr<PhongShader> _lampShader;
  std::unique_ptr<PhongShader> _colorShader;
  std::unique_ptr<PhongShader> _colorNonFlatShader;
  std::unique_ptr<PhongShader> _textureShader;
  std::unique_ptr<LinesShader> _linesShader;
  std::unique_ptr<SkyboxShader> _skyboxShader;
  std::unique_ptr<AStar> _astar;

  Window* _window;
  Camera* _camera;
  std::shared_ptr<EventManager> _eventManager;
  std::unique_ptr<Terrain> _terrain;
  std::unique_ptr<Skybox> _skybox;
  std::unique_ptr<Game> _game;

  glm::mat4& _view;
  glm::mat4& _projection;

  std::function<void(std::unique_ptr<Event> event)> _onEvent;
};

#endif
