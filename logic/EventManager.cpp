#include <iostream>

#include <GL/glew.h>

#include "../globals.h"
#include "EventManager.h"
#include "Hq.h"

glm::vec3 EventManager::unProject(int xpos, int ypos)
{
  GLfloat depth;

  glReadPixels(
    xpos, screenHeight - ypos - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

  glm::vec4 viewport = glm::vec4(0, 0, screenWidth, screenHeight);
  glm::vec3 wincoord = glm::vec3(xpos, screenHeight - ypos - 1, depth);
  glm::vec3 objcoord = glm::unProject(wincoord, gView, gProjection, viewport);
  return objcoord;
}

EventManager::EventManager(GLFWwindow* window,
                           Game& game,
                           Camera& camera,
                           Shader& textureShader,
                           Shader& colorShader,
                           Terrain* terrain) :
  _window(window),
  _camera(camera), _game(game), _textureShader(textureShader),
  _colorShader(colorShader), _terrain(terrain)
{
  _game.setControl(std::make_unique<Control>(textureShader));
}

void EventManager::tick()
{
  _textureShader.use();
  _textureShader.configure();
  if (_selectionActive) {
    _terrain->deselect();
    _terrain->selectSubTerrainRegion(_selection, 0.3f);
  }
  _game.tick();
}

void EventManager::handleKeyPress(GLFWwindow* window,
                                  int key,
                                  int scancode,
                                  int action,
                                  int mods)
{
  if (action == GLFW_RELEASE) {
    if (key == GLFW_KEY_Z) {
      if (_structureSelected) {
        auto factory = dynamic_cast<TankFactory*>(_structureSelected);
        factory->createTank(
          _game, Tank::Type::Medium, HealthLevel::High, Shell::Size::Medium);
      }
    }
    if (key == GLFW_KEY_X) {
      std::cout << "X pressed" << std::endl;
      if (_structureToBuild == nullptr) {
        _structureToBuildStage = BuildStage::SetAngle;
        auto tankFactory = std::make_shared<TankFactory>(
          _textureShader, unProject(currentX, currentY));
        _game.addStructure(tankFactory);
        _structureToBuild = tankFactory;
      } else {
        _structureToBuildStage = BuildStage::Done;
        _structureToBuild->commit();
        _structureToBuild = nullptr;
      }
    }
    if (key == GLFW_KEY_C) {
      std::cout << "C pressed" << std::endl;
      if (_structureToBuild == nullptr) {
        _structureToBuildStage = BuildStage::SetAngle;
        auto hq =
          std::make_shared<Hq>(_textureShader, unProject(currentX, currentY));
        _game.addStructure(hq);
        _structureToBuild = hq;
      } else {
        _structureToBuildStage = BuildStage::Done;
        _structureToBuild->commit();
        _structureToBuild = nullptr;
      }
    }
    if (key == GLFW_KEY_P) {
      auto plant =
        std::make_shared<Plant>(_textureShader, unProject(currentX, currentY));
      _game.addPlant(plant);
    }
    if (key == GLFW_KEY_B) {
      auto barrier = std::make_shared<Barrier>(
        _textureShader, _colorShader, unProject(currentX, currentY));
      _game.addBarrier(barrier);
    }
    if (key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(_window, true);
    }
  } else if (action == GLFW_REPEAT) {
    if (key == GLFW_KEY_UP) {
      _camera.zoomIn();
    }
    if (key == GLFW_KEY_DOWN) {
      _camera.zoomOut();
    }
    if (key == GLFW_KEY_LEFT) {
      _camera.rotateLeft();
    }
    if (key == GLFW_KEY_RIGHT) {
      _camera.rotateRight();
    }
    if (key == GLFW_KEY_W) {
      _camera.moveForward();
    }
    if (key == GLFW_KEY_S) {
      _camera.moveBackward();
    }
    if (key == GLFW_KEY_A) {
      _camera.moveLeft();
    }
    if (key == GLFW_KEY_D) {
      _camera.moveRight();
    }
  } else if (action == GLFW_PRESS) {
  }
}

void EventManager::handleMouseMove(GLFWwindow* window, double xpos, double ypos)
{
  auto c = unProject(currentX, currentY);
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
    auto position = unProject(currentX, currentY);
    if (::abs(position.x) > 10.0f || ::abs(position.y) > 10.0f) {
      position = glm::vec3(10.0f, 10.0f, 0.0f);
    }
    _structureToBuild->setPosition(
      _terrain->getXYZ(glm::vec2(position.x, position.y)));
  }
  if (_selectionActive) {
    _selection.width = c.x - _selection.x;
    _selection.height = c.y - _selection.y;
  }
}

void EventManager::handleMousePressed(int button, int action)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    handleMousePressedLeft();
  } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    handleMousePressedRight();
  } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    handleMouseReleased();
  }
}

void EventManager::handleMouseReleased()
{
  std::cout << "mouse released" << std::endl;
  if (_selection.width != 0 || _selection.height != 0) {
    _tanksSelected = _game.getTanks(_selection);
  }

  _selectionActive = false;
  _selection.width = 0;
  _selection.height = 0;
  _terrain->deselect();
}

void EventManager::handleMousePressedLeft()
{
  auto c = unProject(currentX, currentY);
  _selectionActive = true;
  _selection.x = c.x;
  _selection.y = c.y;
  _tanksSelected.clear();

  _tankSelected = _game.getTank(c, true);
  _structureSelected = _game.getStructure(c);
  _barrierSelected = _game.getBarrier(c);
  if (!_structureSelected) {
    _structureSelected = _game.getStructure(c);
    if (!_structureSelected && _game.panelIsEmpty(Panel::Type::Units)) {
      _game.clearPanel(Panel::Type::Units);
    }
  }
  if (!_barrierSelected) {
    _barrierSelected = _game.getBarrier(c);
    if (!_barrierSelected && _game.panelIsEmpty(Panel::Type::Units)) {
      _game.clearPanel(Panel::Type::Units);
    }
  }
}

void EventManager::handleMousePressedRight()
{
  auto c = unProject(currentX, currentY);
  // TODO remove copypaste for one tank and group of tanks
  if (_tankSelected) {
    _tankUnderAttack = _game.getTank(c);
    _structureUnderAttack = _game.getStructure(c);
    if (_tankUnderAttack) {
      _tankSelected->startShooting(_tankUnderAttack);
    } else if (_structureUnderAttack) {
      _tankSelected->startShooting(_structureUnderAttack);
    } else {
      _tankSelected->startMoving(c);
    }
  }
  if (_structureToBuild &&
      (_structureToBuildStage == BuildStage::SetPosition)) {
    _structureToBuildStage = BuildStage::SetAngle;
  } else if (_structureToBuild &&
             (_structureToBuildStage == BuildStage::SetAngle)) {
    _structureToBuildStage = BuildStage::Done;
    _structureToBuild->commit();
    _structureToBuild = nullptr;
  } else if (!_tanksSelected.empty()) {
    _tankUnderAttack = _game.getTank(c);
    _structureUnderAttack = _game.getStructure(c);
    if (_tankUnderAttack) {
      _tanksSelected.startShooting(_tankUnderAttack);
    } else if (_structureUnderAttack) {
      _tanksSelected.startShooting(_structureUnderAttack);
    } else {
      _tanksSelected.startMoving(c);
    }
  }
}

void EventManager::setStructureToBuild(
  std::shared_ptr<BuildableStructure> structure)
{
  _structureToBuild = structure;
}

void EventManager::setStructureToBuildStage(BuildStage stage)
{
  _structureToBuildStage = stage;
}
