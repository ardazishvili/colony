#ifndef COLONY_EVENTS_H
#define COLONY_EVENTS_H

#include <iostream>

#include <GL/glew.h> // Initialize with glewInit()
#include <GLFW/glfw3.h>

#include "../../logic/EventManager.h"
#include "../../logic/Hq.h"
#include "../../logic/Turbine.h"
#include "../Window.h"
#include "Event.h"

class ErrorEvent : public Event
{
public:
  void process(Camera* camera, EventManager* eventManager) override
  {
    std::cout << "ErrorEvent test output" << std::endl;
  }
};

class ColonyKeyPressEvent : public KeyboardPressEvent
{
public:
  ColonyKeyPressEvent(GLFWwindow* window,
                      int key,
                      int scancode,
                      int action,
                      int mods) :
    _window(window),
    _key(key), _scancode(), _action(action), _mods(mods)
  {
  }
  void process(Camera* camera, EventManager* eventManager)
  {
    if (_action == GLFW_PRESS) {
      if (_key == GLFW_KEY_LEFT_SHIFT) {
        eventManager->_shiftPressed = true;
      }
    }
    if (_action == GLFW_RELEASE) {
      if (_key == GLFW_KEY_LEFT_SHIFT) {
        eventManager->_shiftPressed = false;
      }
      if (_key == GLFW_KEY_Z) {
        if (eventManager->_structureSelected) {
          auto factory =
            dynamic_cast<TankFactory*>(eventManager->_structureSelected);
          factory->createTank(eventManager->_game,
                              Tank::Type::Medium,
                              HealthLevel::High,
                              Shell::Size::Medium);
        }
      }
      if (_key == GLFW_KEY_X) {
        std::cout << "X pressed" << std::endl;
        if (eventManager->_structureToBuild == nullptr) {
          eventManager->_structureToBuildStage = BuildStage::SetAngle;
          auto tankFactory = std::make_shared<TankFactory>(
            eventManager->_textureShader,
            eventManager->_linesShader,
            eventManager->_astar,
            EventManager::unProject(eventManager->_window,
                                    eventManager->_view,
                                    eventManager->_projection));
          eventManager->_game->addStructure(tankFactory);
          eventManager->_structureToBuild = tankFactory;
        } else {
          eventManager->_structureToBuild->commit();
          eventManager->_structureToBuild = nullptr;
        }
      }
      if (_key == GLFW_KEY_C) {
        std::cout << "C pressed" << std::endl;
        if (eventManager->_structureToBuild == nullptr) {
          eventManager->_structureToBuildStage = BuildStage::SetAngle;
          auto hq = std::make_shared<Hq>(
            eventManager->_game,
            eventManager,
            eventManager->_textureShader,
            eventManager->_linesShader,
            eventManager->_astar,
            EventManager::unProject(eventManager->_window,
                                    eventManager->_view,
                                    eventManager->_projection),
            eventManager->_terrain);
          eventManager->_game->addStructure(hq);
          eventManager->_structureToBuild = hq;
        } else {
          eventManager->_structureToBuild->commit();
          eventManager->_structureToBuild = nullptr;
        }
      }
      if (_key == GLFW_KEY_B) {
        std::cout << "B pressed" << std::endl;
        if (eventManager->_structureToBuild == nullptr) {
          eventManager->_structureToBuildStage = BuildStage::SetAngle;
          auto b = std::make_shared<Barrier>(
            eventManager->_textureShader,
            eventManager->_linesShader,
            EventManager::unProject(eventManager->_window,
                                    eventManager->_view,
                                    eventManager->_projection),
            eventManager->_terrain,
            eventManager->_astar);
          eventManager->_game->addStructure(b);
          eventManager->_game->addShroud(b->shroud());
          eventManager->_structureToBuild = b;
        } else {
          eventManager->_structureToBuild->commit();
          eventManager->_structureToBuild = nullptr;
        }
      }
      if (_key == GLFW_KEY_T) {
        std::cout << "T pressed" << std::endl;
        if (eventManager->_structureToBuild == nullptr) {
          eventManager->_structureToBuildStage = BuildStage::SetAngle;
          auto b = std::make_shared<Turbine>(
            eventManager->_textureShader,
            eventManager->_linesShader,
            eventManager->_game,
            EventManager::unProject(eventManager->_window,
                                    eventManager->_view,
                                    eventManager->_projection));
          eventManager->_game->addStructure(b);
          eventManager->_structureToBuild = b;
        } else {
          eventManager->_structureToBuild->commit();
          eventManager->_structureToBuild = nullptr;
        }
      }
      if (_key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(eventManager->_window->_window, true);
      }
    } else if (_action == GLFW_REPEAT) {
      if (_key == GLFW_KEY_LEFT) {
        camera->rotateLeft();
      }
      if (_key == GLFW_KEY_RIGHT) {
        camera->rotateRight();
      }
      if (_key == GLFW_KEY_W) {
        camera->moveForward();
      }
      if (_key == GLFW_KEY_S) {
        camera->moveBackward();
      }
      if (_key == GLFW_KEY_A) {
        camera->moveLeft();
      }
      if (_key == GLFW_KEY_D) {
        camera->moveRight();
      }
    } else if (_action == GLFW_PRESS) {
    }
  }

private:
  GLFWwindow* _window;
  int _key;
  int _scancode;
  int _action;
  int _mods;
};

#endif
