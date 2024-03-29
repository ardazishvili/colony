#include "figImpl/ColonyEventManager.h"

#include "fig/GlfwWindow.h"
#include "fig/globals.h"
#include "logic/structures/Hq.h"
#include "logic/structures/Turbine.h"

ColonyEventManager::ColonyEventManager(
    glm::mat4& view, glm::mat4& projection, fig::Window& window, Game& game,
    fig::Camera& camera, fig::Terrain& terrain,
    std::unique_ptr<fig::ObstaclesSegment> mapObstacles, fig::AStar& astar)
    : _view(view),
      _projection(projection),
      _window(window),
      _camera(camera),
      _game(game),
      _terrain(terrain),
      _selection(*SHADERS_MAP[ShaderType::LINES], camera),
      _mapObstacles(std::move(mapObstacles)),
      _astar(astar) {
  _game.setControl(
      std::make_unique<Control>(_game, this, _window, _terrain, _astar));
}

void ColonyEventManager::tick() {
  if (_selectionActive) {
    _selection.render();
  }
  if (_heightsSegment) {
    _heightsSegment->render();
  }
  if (_obstaclesSegment) {
    _obstaclesSegment->render();
  }
  _game.tick();
}

void ColonyEventManager::setStructureToBuild(GroundStructure* structure) {
  _structureToBuild = structure;
}

void ColonyEventManager::setStructureToBuildStage(BuildStage stage) {
  _structureToBuildStage = stage;
}
