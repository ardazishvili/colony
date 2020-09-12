

#include "ColonyKeyReleaseEvent.h"
#include "../../logic/Hq.h"
#include "../../logic/Turbine.h"
#include "../ColonyEventManager.h"

/* #include "../../fig/GlfwWindow.h" */

ColonyKeyReleaseEvent::ColonyKeyReleaseEvent(int key, int scancode, int mods) :
  KeyboardReleaseEvent(key, scancode, mods)
{
}

void ColonyKeyReleaseEvent::process(fig::Camera* camera,
                                    fig::EventManager* eventManager)
{
  // TODO downcast
  auto em = dynamic_cast<ColonyEventManager*>(eventManager);

  if (_key == GLFW_KEY_LEFT_SHIFT) {
    em->releaseKey(fig::KeyButton::LEFT_SHIFT);
  }
  if (_key == GLFW_KEY_Z) {
    if (em->_structureSelected) {
      auto factory = dynamic_cast<TankFactory*>(em->_structureSelected);
      factory->createTank(
        em->_game, Tank::Type::Medium, HealthLevel::High, Shell::Size::Medium);
    }
  }
  if (_key == GLFW_KEY_X) {
    std::cout << "X pressed" << std::endl;
    if (em->_structureToBuild == nullptr) {
      em->_structureToBuildStage = BuildStage::SetAngle;
      auto tankFactory = std::make_shared<TankFactory>(
        em->_textureShader,
        em->_linesShader,
        em->_astar,
        fig::EventManager::unProject(em->_window, em->_view, em->_projection));
      em->_game->addStructure(tankFactory);
      em->_structureToBuild = tankFactory;
    } else {
      em->_structureToBuild->commit();
      em->_structureToBuild = nullptr;
    }
  }
  if (_key == GLFW_KEY_C) {
    std::cout << "C pressed" << std::endl;
    if (em->_structureToBuild == nullptr) {
      em->_structureToBuildStage = BuildStage::SetAngle;
      auto hq = std::make_shared<Hq>(
        em->_game,
        em,
        em->_textureShader,
        em->_linesShader,
        em->_astar,
        fig::EventManager::unProject(em->_window, em->_view, em->_projection),
        em->_terrain);
      em->_game->addStructure(hq);
      em->_structureToBuild = hq;
    } else {
      em->_structureToBuild->commit();
      em->_structureToBuild = nullptr;
    }
  }
  if (_key == GLFW_KEY_B) {
    std::cout << "B pressed" << std::endl;
    if (em->_structureToBuild == nullptr) {
      em->_structureToBuildStage = BuildStage::SetAngle;
      auto b = std::make_shared<Barrier>(
        em->_textureShader,
        em->_linesShader,
        fig::EventManager::unProject(em->_window, em->_view, em->_projection),
        em->_terrain,
        em->_astar);
      em->_game->addStructure(b);
      em->_game->addShroud(b->shroud());
      em->_structureToBuild = b;
    } else {
      em->_structureToBuild->commit();
      em->_structureToBuild = nullptr;
    }
  }
  if (_key == GLFW_KEY_T) {
    std::cout << "T pressed" << std::endl;
    if (em->_structureToBuild == nullptr) {
      em->_structureToBuildStage = BuildStage::SetAngle;
      auto b = std::make_shared<Turbine>(
        em->_textureShader,
        em->_linesShader,
        em->_game,
        fig::EventManager::unProject(em->_window, em->_view, em->_projection));
      em->_game->addStructure(b);
      em->_structureToBuild = b;
    } else {
      em->_structureToBuild->commit();
      em->_structureToBuild = nullptr;
    }
  }
  if (_key == GLFW_KEY_ESCAPE) {
    em->_window->close();
  }
}
