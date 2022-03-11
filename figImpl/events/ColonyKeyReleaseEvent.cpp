#include "figImpl/events/ColonyKeyReleaseEvent.h"

#include <GLFW/glfw3.h>

#include <memory>

#include "EventManager.h"
#include "figImpl/ColonyEventManager.h"
#include "logic/structures/Barrier.h"
#include "logic/structures/Hq.h"
#include "logic/structures/TankFactory.h"
#include "logic/structures/Turbine.h"
#include "logic/units/Tank.h"

ColonyKeyReleaseEvent::ColonyKeyReleaseEvent(int key, int scancode, int mods)
    : KeyboardReleaseEvent(key, scancode, mods) {
  _handler.setAction("Build tank factory", [this](fig::EventManager* manager) {
    buildTankFactory(manager);
  });
  _handler.setAction("Create tank", [this](fig::EventManager* manager) {
    createTank(manager);
  });
  _handler.setAction("Build HQ",
                     [this](fig::EventManager* manager) { buildHq(manager); });
  _handler.setAction("Build Barrier", [this](fig::EventManager* manager) {
    buildBarrier(manager);
  });
  _handler.setAction("Build Turbine", [this](fig::EventManager* manager) {
    buildTurbine(manager);
  });

  _handler.setHandler(
      GLFW_KEY_LEFT_SHIFT,
      [this](fig::EventManager* manager) { processLEFT_SHIFT(manager); },
      "LEFT_SHIFT handler");
  _handler.setHandler(
      GLFW_KEY_ESCAPE,
      [this](fig::EventManager* manager) { closeWindow(manager); },
      "Close window");
}
void ColonyKeyReleaseEvent::buildTankFactory(fig::EventManager* eventManager) {
  // TODO downcast
  auto* manager = dynamic_cast<ColonyEventManager*>(eventManager);
  if (manager->_structureToBuild == nullptr) {
    manager->_structureToBuildStage = BuildStage::SetAngle;
    auto tankFactory = std::make_unique<TankFactory>(
        manager->_astar,
        fig::EventManager::unProject(manager->_window, manager->_view,
                                     manager->_projection));
    manager->setStructureToBuild(tankFactory.get());
    manager->_game.addStructure(std::move(tankFactory));
  } else {
    manager->_structureToBuild->commit();
    manager->_structureToBuild = nullptr;
  }
}

void ColonyKeyReleaseEvent::createTank(fig::EventManager* eventManager) {
  // TODO downcast
  auto* manager = dynamic_cast<ColonyEventManager*>(eventManager);

  if (manager->_structureSelected) {
    auto factory = dynamic_cast<TankFactory*>(manager->_structureSelected);
    factory->createTank(manager->_game, Tank::Type::Medium, HealthLevel::High,
                        Shell::Size::Medium);
  }
}

void ColonyKeyReleaseEvent::buildHq(fig::EventManager* eventManager) {
  // TODO downcast
  auto* manager = dynamic_cast<ColonyEventManager*>(eventManager);

  if (manager->_structureToBuild == nullptr) {
    manager->_structureToBuildStage = BuildStage::SetAngle;
    auto hq = std::make_unique<Hq>(
        manager, manager->_astar,
        fig::EventManager::unProject(manager->_window, manager->_view,
                                     manager->_projection),
        manager->_terrain);
    manager->setStructureToBuild(hq.get());
    manager->_game.addStructure(std::move(hq));
  } else {
    manager->_structureToBuild->commit();
    manager->_structureToBuild = nullptr;
  }
}
void ColonyKeyReleaseEvent::buildBarrier(fig::EventManager* eventManager) {
  // TODO downcast
  auto* manager = dynamic_cast<ColonyEventManager*>(eventManager);

  if (manager->_structureToBuild == nullptr) {
    manager->_structureToBuildStage = BuildStage::SetAngle;
    auto barrier = std::make_unique<Barrier>(
        fig::EventManager::unProject(manager->_window, manager->_view,
                                     manager->_projection),
        manager->_terrain, manager->_astar);
    manager->_game.addShroud(barrier->shroud());
    manager->setStructureToBuild(barrier.get());
    manager->_game.addStructure(std::move(barrier));
  } else {
    manager->_structureToBuild->commit();
    manager->_structureToBuild = nullptr;
  }
}
void ColonyKeyReleaseEvent::buildTurbine(fig::EventManager* eventManager) {
  // TODO downcast
  auto* manager = dynamic_cast<ColonyEventManager*>(eventManager);

  if (manager->_structureToBuild == nullptr) {
    manager->_structureToBuildStage = BuildStage::SetAngle;
    auto turbine = std::make_unique<Turbine>(
        manager->_game,
        fig::EventManager::unProject(manager->_window, manager->_view,
                                     manager->_projection));
    manager->setStructureToBuild(turbine.get());
    manager->_game.addStructure(std::move(turbine));
  } else {
    manager->_structureToBuild->commit();
    manager->_structureToBuild = nullptr;
  }
}

void ColonyKeyReleaseEvent::processLEFT_SHIFT(fig::EventManager* eventManager) {
  // TODO downcast
  auto* manager = dynamic_cast<ColonyEventManager*>(eventManager);

  manager->releaseKey(fig::KeyButton::LEFT_SHIFT);
}

void ColonyKeyReleaseEvent::closeWindow(fig::EventManager* eventManager) {
  // TODO downcast
  auto* manager = dynamic_cast<ColonyEventManager*>(eventManager);

  manager->_window.close();
}
