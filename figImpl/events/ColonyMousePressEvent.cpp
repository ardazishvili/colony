#include "figImpl/events/ColonyMousePressEvent.h"

#include <GLFW/glfw3.h>

#include "figImpl/ColonyEventManager.h"

ColonyMousePressedEvent::ColonyMousePressedEvent(int button)
    : MousePressEvent(button) {}

void ColonyMousePressedEvent::process(fig::Camera* camera,
                                      fig::EventManager* eventManager) {
  if (_button == GLFW_MOUSE_BUTTON_MIDDLE) {
    handleMousePressedMiddle(eventManager);
  }
  if (_button == GLFW_MOUSE_BUTTON_LEFT) {
    handleMousePressedLeft(eventManager);
  }
  if (_button == GLFW_MOUSE_BUTTON_RIGHT) {
    handleMousePressedRight(eventManager);
  }
}

void ColonyMousePressedEvent::handleMousePressedLeft(
    fig::EventManager* manager) {
  // TODO downcast
  auto eventManager = dynamic_cast<ColonyEventManager*>(manager);

  auto c = fig::EventManager::unProject(
      eventManager->_window, eventManager->_view, eventManager->_projection);
  eventManager->_selectionActive = true;
  auto tmp = c;
  tmp.z += 0.3;
  eventManager->clearHeightSegment();
  eventManager->_obstaclesSegment.reset();
  eventManager->_selection.setStart(tmp);

  eventManager->_tankSelected = eventManager->_game.getAttackUnit(c, true);
  eventManager->_structureSelected = eventManager->_game.getStructure(c);
  if (!eventManager->_structureSelected) {
    eventManager->_structureSelected = eventManager->_game.getStructure(c);
    if (!eventManager->_structureSelected &&
        eventManager->_game.panelIsEmpty(Panel::Type::Units)) {
      eventManager->_game.clearPanel(Panel::Type::Units);
    }
  }
}

void ColonyMousePressedEvent::handleMousePressedRight(
    fig::EventManager* eventManager) {
  // TODO downcast
  auto m = dynamic_cast<ColonyEventManager*>(eventManager);

  auto c = fig::EventManager::unProject(m->_window, m->_view, m->_projection);
  // TODO remove copypaste for one tank and group of tanks
  if (m->_tankSelected) {
    m->_tankUnderAttack = m->_game.getAttackUnit(c);
    m->_structureUnderAttack = m->_game.getStructure(c);
    if (m->_tankUnderAttack) {
      m->_tankSelected->startShooting(m->_tankUnderAttack);
    } else if (m->_structureUnderAttack) {
      m->_tankSelected->startShooting(m->_structureUnderAttack);
    } else {
      m->_tankSelected->setRoute(c);
    }
  }
  if (m->_structureToBuild &&
      (m->_structureToBuildStage == BuildStage::SetPosition)) {
    std::cout << "setting position" << std::endl;
    m->_structureToBuildStage = BuildStage::SetAngle;
  } else if (m->_structureToBuild &&
             (m->_structureToBuildStage == BuildStage::SetAngle)) {
    std::cout << "setting angle" << std::endl;
    m->_structureToBuild->commit();
    m->_structureToBuild = nullptr;
  } else if (!m->_tanksSelected.empty()) {
    m->_tankUnderAttack = m->_game.getAttackUnit(c);
    m->_structureUnderAttack = m->_game.getStructure(c);
    if (m->_tankUnderAttack) {
      m->_tanksSelected.startShooting(m->_tankUnderAttack);
    } else if (m->_structureUnderAttack) {
      m->_tanksSelected.startShooting(m->_structureUnderAttack);
    } else {
      m->_tanksSelected.setRoute(c);
    }
  }
}

void ColonyMousePressedEvent::handleMousePressedMiddle(
    fig::EventManager* eventManager) {
  // TODO downcast
  auto m = dynamic_cast<ColonyEventManager*>(eventManager);

  m->pressMouse(fig::MouseButton::MIDDLE);
  double xpos, ypos;
  m->_window.getCursorPos(&xpos, &ypos);
  m->_middleLastPressed = glm::vec2(xpos, ypos);
}
