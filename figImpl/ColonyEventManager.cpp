#include "../fig/GlfwWindow.h"
#include "../fig/globals.h"

#include "../logic/Hq.h"
#include "../logic/Turbine.h"
#include "ColonyEventManager.h"

ColonyEventManager::ColonyEventManager(glm::mat4& view,
                                       glm::mat4& projection,
                                       fig::Window* window,
                                       Game* game,
                                       fig::Camera& camera,
                                       fig::Shader& textureShader,
                                       fig::Shader& colorShader,
                                       fig::Shader& colorNonFlatShader,
                                       fig::Shader& linesShader,
                                       fig::Terrain* terrain,
                                       std::shared_ptr<fig::ObstaclesSegment> mo,
                                       fig::AStar* astar) :
  _view(view),
  _projection(projection), _window(window), _camera(camera), _game(game), _textureShader(textureShader),
  _colorShader(colorShader), _colorNonFlatShader(colorNonFlatShader), _linesShader(linesShader), _terrain(terrain),
  _selection(linesShader, camera), _mapObstacles(mo), _astar(astar)
{
  // TODO downcast
  _game->setControl(std::make_unique<Control>(_game, this, _window, textureShader, linesShader, _terrain, _astar));
}

void ColonyEventManager::tick()
{
  _textureShader.use();
  _textureShader.configure();
  if (_selectionActive) {
    _selection.render();
  }
  if (_heightsSegment) {
    _heightsSegment->render();
  }
  if (_obstaclesSegment) {
    _obstaclesSegment->render();
  }
  _game->tick();
}

void ColonyEventManager::setStructureToBuild(std::shared_ptr<GroundStructure> structure)
{
  _structureToBuild = structure;
}

void ColonyEventManager::setStructureToBuildStage(BuildStage stage)
{
  _structureToBuildStage = stage;
}
