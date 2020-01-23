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

void EventManager::handleMouseMove(GLFWwindow* window, double xpos, double ypos)
{
  if (_shiftPressed && _middleButtonPressed) {
    auto deltaX = xpos - _middleLastPressed.x;
    auto deltaY = ypos - _middleLastPressed.y;

    if (deltaY < 0) {
      _camera.moveBackward();
    } else if (deltaY > 0) {
      _camera.moveForward();
    }
    if (deltaX > 0) {
      _camera.moveLeft();
    } else if (deltaX < 0) {
      _camera.moveRight();
    }
    _middleLastPressed = glm::vec2(xpos, ypos);
  } else if (_middleButtonPressed) {
    auto deltaX = xpos - _middleLastPressed.x;
    auto deltaY = ypos - _middleLastPressed.y;

    if (deltaY < 0) {
      _camera.rotateUp();
    } else if (deltaY > 0) {
      _camera.rotateDown();
    }
    if (deltaX > 0) {
      _camera.rotateLeft();
    } else if (deltaX < 0) {
      _camera.rotateRight();
    }
    _middleLastPressed = glm::vec2(xpos, ypos);
  }
  auto c = unProject(_window, _view, _projection);
  if (_structureToBuild && (_structureToBuildStage == BuildStage::SetAngle)) {
    float structureX = _structureToBuild->position().x;
    float structureY = _structureToBuild->position().y;
    float radianAngle = ::atan((structureY - c.y) / (structureX - c.x));
    float degreeAngle = radianAngle * 180.0f / M_PI;
    if (structureX - c.x < 0) {
      degreeAngle += 180.0f;
    }

    _structureToBuild->setAngle(degreeAngle);
  } else if (_structureToBuild &&
             (_structureToBuildStage == BuildStage::SetPosition)) {
    auto position = unProject(_window, _view, _projection);
    auto maxXy = _terrain->getMaxXy();
    if (::abs(position.x) > maxXy || ::abs(position.y) > maxXy) {
      position = glm::vec3(maxXy, maxXy, 0.0f);
    }
    _structureToBuild->setPosition(
      _terrain->getXYZ(glm::vec2(position.x, position.y)));
  }
  if (_selectionActive) {
    auto tmp = c;
    tmp.z += 0.3;
    _selection.setEnd(tmp);
  }
}

void EventManager::handleMousePressed(int button, int action)
{
  if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
    handleMousePressedMiddle();
  }
  if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) {
    handleMouseReleasedMiddle();
  }
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    handleMousePressedLeft();
  } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    handleMousePressedRight();
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    handleMouseReleased();
  }
}

void EventManager::handleMousePressedMiddle()
{
  _middleButtonPressed = true;
  double xpos, ypos;
  _window->getCursorPos(&xpos, &ypos);
  _middleLastPressed = glm::vec2(xpos, ypos);
}

void EventManager::handleMouseReleasedMiddle()
{
  _middleButtonPressed = false;
}

void EventManager::handleMouseReleased()
{
  std::cout << "mouse released" << std::endl;
  if (_shiftPressed) {

    auto bl = _selection.bottomLeft();
    auto tr = _selection.topRight();
    _heightsSegment =
      ::makeHeightsSegment(_colorNonFlatShader,
                           _terrain,
                           glm::vec2(::min(bl.x, tr.x), ::min(bl.y, tr.y)),
                           glm::vec2(::max(bl.x, tr.x), ::max(bl.y, tr.y)));
    _obstaclesSegment =
      ::makeObstaclesSegment(_colorNonFlatShader,
                             _terrain,
                             glm::vec2(::min(bl.x, tr.x), ::min(bl.y, tr.y)),
                             glm::vec2(::max(bl.x, tr.x), ::max(bl.y, tr.y)));
  } else {

    _tanksSelected = _game->getTanks(_selection.getPoints());
  }

  _selectionActive = false;
  _selection.clear();
}

void EventManager::handleMousePressedLeft()
{
  auto c = unProject(_window, _view, _projection);
  _selectionActive = true;
  auto tmp = c;
  tmp.z += 0.3;
  _heightsSegment.reset();
  _obstaclesSegment.reset();
  _selection.setStart(tmp);

  _tankSelected = _game->getAttackUnit(c, true);
  _structureSelected = _game->getStructure(c);
  if (!_structureSelected) {
    _structureSelected = _game->getStructure(c);
    if (!_structureSelected && _game->panelIsEmpty(Panel::Type::Units)) {
      _game->clearPanel(Panel::Type::Units);
    }
  }
}

void EventManager::handleMousePressedRight()
{
  auto c = unProject(_window, _view, _projection);
  // TODO remove copypaste for one tank and group of tanks
  if (_tankSelected) {
    _tankUnderAttack = _game->getAttackUnit(c);
    _structureUnderAttack = _game->getStructure(c);
    if (_tankUnderAttack) {
      _tankSelected->startShooting(_tankUnderAttack);
    } else if (_structureUnderAttack) {
      _tankSelected->startShooting(_structureUnderAttack);
    } else {
      _tankSelected->setRoute(c);
    }
  }
  if (_structureToBuild &&
      (_structureToBuildStage == BuildStage::SetPosition)) {
    std::cout << "setting position" << std::endl;
    _structureToBuildStage = BuildStage::SetAngle;
  } else if (_structureToBuild &&
             (_structureToBuildStage == BuildStage::SetAngle)) {
    std::cout << "setting angle" << std::endl;
    _structureToBuild->commit();
    _structureToBuild = nullptr;
  } else if (!_tanksSelected.empty()) {
    _tankUnderAttack = _game->getAttackUnit(c);
    _structureUnderAttack = _game->getStructure(c);
    if (_tankUnderAttack) {
      _tanksSelected.startShooting(_tankUnderAttack);
    } else if (_structureUnderAttack) {
      _tanksSelected.startShooting(_structureUnderAttack);
    } else {
      _tanksSelected.setRoute(c);
    }
  }
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

