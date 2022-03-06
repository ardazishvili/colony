#include "figImpl/events/ColonyKeyReleaseEvent.h"

#include <GLFW/glfw3.h>

#include <memory>

#include "figImpl/ColonyEventManager.h"
#include "logic/structures/Barrier.h"
#include "logic/structures/Hq.h"
#include "logic/structures/TankFactory.h"
#include "logic/structures/Turbine.h"

ColonyKeyReleaseEvent::ColonyKeyReleaseEvent(int key, int scancode, int mods)
    : KeyboardReleaseEvent(key, scancode, mods) {}

void ColonyKeyReleaseEvent::process(fig::Camera* camera,
                                    fig::EventManager* eventManager) {
  // TODO downcast
  auto em = dynamic_cast<ColonyEventManager*>(eventManager);

  if (_key == GLFW_KEY_LEFT_SHIFT) {
    em->releaseKey(fig::KeyButton::LEFT_SHIFT);
  }
  if (_key == GLFW_KEY_Z) {
    if (em->_structureSelected) {
      auto factory = dynamic_cast<TankFactory*>(em->_structureSelected);
      factory->createTank(em->_game, Tank::Type::Medium, HealthLevel::High,
                          Shell::Size::Medium);
    }
  }
  if (_key == GLFW_KEY_X) {
    std::cout << "X pressed" << std::endl;
    if (em->_structureToBuild == nullptr) {
      em->_structureToBuildStage = BuildStage::SetAngle;
      auto tankFactory = std::make_unique<TankFactory>(
          em->_astar, fig::EventManager::unProject(em->_window, em->_view,
                                                   em->_projection));
      em->setStructureToBuild(tankFactory.get());
      em->_game.addStructure(std::move(tankFactory));
    } else {
      em->_structureToBuild->commit();
      em->_structureToBuild = nullptr;
    }
  }
  if (_key == GLFW_KEY_C) {
    std::cout << "C pressed" << std::endl;
    if (em->_structureToBuild == nullptr) {
      em->_structureToBuildStage = BuildStage::SetAngle;
      auto hq = std::make_unique<Hq>(
          em, em->_astar,
          fig::EventManager::unProject(em->_window, em->_view, em->_projection),
          em->_terrain);
      em->setStructureToBuild(hq.get());
      em->_game.addStructure(std::move(hq));
    } else {
      em->_structureToBuild->commit();
      em->_structureToBuild = nullptr;
    }
  }
  if (_key == GLFW_KEY_B) {
    std::cout << "B pressed" << std::endl;
    if (em->_structureToBuild == nullptr) {
      em->_structureToBuildStage = BuildStage::SetAngle;
      auto barrier = std::make_unique<Barrier>(
          fig::EventManager::unProject(em->_window, em->_view, em->_projection),
          em->_terrain, em->_astar);
      em->_game.addShroud(barrier->shroud());
      em->setStructureToBuild(barrier.get());
      em->_game.addStructure(std::move(barrier));
    } else {
      em->_structureToBuild->commit();
      em->_structureToBuild = nullptr;
    }
  }
  if (_key == GLFW_KEY_T) {
    std::cout << "T pressed" << std::endl;
    if (em->_structureToBuild == nullptr) {
      em->_structureToBuildStage = BuildStage::SetAngle;
      auto turbine = std::make_unique<Turbine>(
          em->_game, fig::EventManager::unProject(em->_window, em->_view,
                                                  em->_projection));
      em->setStructureToBuild(turbine.get());
      em->_game.addStructure(std::move(turbine));
    } else {
      em->_structureToBuild->commit();
      em->_structureToBuild = nullptr;
    }
  }
  if (_key == GLFW_KEY_ESCAPE) {
    em->_window.close();
  }
}
