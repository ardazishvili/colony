#include "ColonyKeyReleaseEvent.h"
#include "../../logic/EventManager.h"
#include "../../logic/Hq.h"
#include "../../logic/Turbine.h"
#include "../ColonyWindow.h"

ColonyKeyReleaseEvent::ColonyKeyReleaseEvent(GLFWwindow* window,
                                             int key,
                                             int scancode,
                                             int mods) :
  KeyboardReleaseEvent(window, key, scancode, mods)
{
}

void ColonyKeyReleaseEvent::process(Camera* camera, EventManager* eventManager)
{
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
      auto hq =
        std::make_shared<Hq>(eventManager->_game,
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
}
