#include <iostream>

#include <GL/glew.h>

#include "../engine/Window.h"
#include "../globals.h"
#include "EventManager.h"
#include "Hq.h"
#include "Turbine.h"

glm::vec3 EventManager::unProject(Window* window,
                                  glm::mat4& view,
                                  glm::mat4& proj)
{
  GLfloat depth;

  double xpos, ypos;
  window->getCursorPos(&xpos, &ypos);
  glReadPixels(xpos,
               window->height() - ypos - 1,
               1,
               1,
               GL_DEPTH_COMPONENT,
               GL_FLOAT,
               &depth);

  glm::vec4 viewport = glm::vec4(0, 0, window->width(), window->height());
  glm::vec3 wincoord = glm::vec3(xpos, window->height() - ypos - 1, depth);
  glm::vec3 objcoord = glm::unProject(wincoord, view, proj, viewport);
  return objcoord;
}

EventManager::EventManager(glm::mat4& view,
                           glm::mat4& projection,
                           Window* window,
                           Game* game,
                           Camera& camera,
                           Shader& textureShader,
                           Shader& colorShader,
                           Shader& colorNonFlatShader,
                           Shader& linesShader,
                           Terrain* terrain,
                           std::shared_ptr<ObstaclesSegment> mo,
                           AStar* astar) :
  _view(view),
  _projection(projection), _window(window), _camera(camera), _game(game),
  _textureShader(textureShader), _colorShader(colorShader),
  _colorNonFlatShader(colorNonFlatShader), _linesShader(linesShader),
  _terrain(terrain), _selection(linesShader, camera), _mapObstacles(mo),
  _astar(astar)
{
  _game->setControl(std::make_unique<Control>(_game,
                                              this,
                                              _window->_window,
                                              textureShader,
                                              linesShader,
                                              _terrain,
                                              _astar));
}

void EventManager::tick()
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

void EventManager::setStructureToBuild(
  std::shared_ptr<GroundStructure> structure)
{
  _structureToBuild = structure;
}

void EventManager::setStructureToBuildStage(BuildStage stage)
{
  _structureToBuildStage = stage;
}

