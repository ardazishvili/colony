#include "ColonyMouseReleaseEvent.h"
#include "../ColonyEventManager.h"

ColonyMouseReleaseEvent::ColonyMouseReleaseEvent(int button) :
  MouseReleaseEvent(button)
{
}

void ColonyMouseReleaseEvent::process(fig::Camera* camera,
                                      fig::EventManager* eventManager)
{
  if (_button == GLFW_MOUSE_BUTTON_MIDDLE) {
    handleMouseReleasedMiddle(eventManager);
  } else if (_button == GLFW_MOUSE_BUTTON_LEFT) {
    handleMouseReleased(eventManager);
  }
}

void ColonyMouseReleaseEvent::handleMouseReleasedMiddle(
  fig::EventManager* eventManager)
{
  // TODO downcast
  auto m = dynamic_cast<ColonyEventManager*>(eventManager);

  m->releaseMouse(fig::MouseButton::MIDDLE);
}

void ColonyMouseReleaseEvent::handleMouseReleased(
  fig::EventManager* eventManager)
{
  // TODO downcast
  auto m = dynamic_cast<ColonyEventManager*>(eventManager);

  if (m->isKeyPressed(fig::KeyButton::LEFT_SHIFT)) {

    auto bl = m->_selection.bottomLeft();
    auto tr = m->_selection.topRight();
    m->_heightsSegment = fig::makeHeightsSegment(
      m->_colorNonFlatShader,
      m->_terrain,
      glm::vec2(std::min(bl.x, tr.x), std::min(bl.y, tr.y)),
      glm::vec2(std::max(bl.x, tr.x), std::max(bl.y, tr.y)));
    m->_obstaclesSegment = fig::makeObstaclesSegment(
      m->_colorNonFlatShader,
      m->_terrain,
      glm::vec2(std::min(bl.x, tr.x), std::min(bl.y, tr.y)),
      glm::vec2(std::max(bl.x, tr.x), std::max(bl.y, tr.y)));
  } else {
    m->_tanksSelected = m->_game->getTanks(m->_selection.getPoints());
  }
  m->_selectionActive = false;
  m->_selection.clear();
}
