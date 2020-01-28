#include "ColonyMouseReleaseEvent.h"
#include "../ColonyEventManager.h"

ColonyMouseReleaseEvent::ColonyMouseReleaseEvent(int button) :
  MouseReleaseEvent(button)
{
}

void ColonyMouseReleaseEvent::process(Camera* camera,
                                      EventManager* eventManager)
{
  if (_button == GLFW_MOUSE_BUTTON_MIDDLE) {
    handleMouseReleasedMiddle(eventManager);
  } else if (_button == GLFW_MOUSE_BUTTON_LEFT) {
    handleMouseReleased(eventManager);
  }
}

void ColonyMouseReleaseEvent::handleMouseReleasedMiddle(
  EventManager* eventManager)
{
  // TODO downcast
  auto m = dynamic_cast<ColonyEventManager*>(eventManager);

  m->releaseMouse(MouseButton::MIDDLE);
}

void ColonyMouseReleaseEvent::handleMouseReleased(EventManager* eventManager)
{
  // TODO downcast
  auto m = dynamic_cast<ColonyEventManager*>(eventManager);

  std::cout << "mouse released" << std::endl;
  if (m->isKeyPressed(KeyButton::LEFT_SHIFT)) {

    auto bl = m->_selection.bottomLeft();
    auto tr = m->_selection.topRight();
    m->_heightsSegment =
      ::makeHeightsSegment(m->_colorNonFlatShader,
                           m->_terrain,
                           glm::vec2(::min(bl.x, tr.x), ::min(bl.y, tr.y)),
                           glm::vec2(::max(bl.x, tr.x), ::max(bl.y, tr.y)));
    m->_obstaclesSegment =
      ::makeObstaclesSegment(m->_colorNonFlatShader,
                             m->_terrain,
                             glm::vec2(::min(bl.x, tr.x), ::min(bl.y, tr.y)),
                             glm::vec2(::max(bl.x, tr.x), ::max(bl.y, tr.y)));
  } else {
    m->_tanksSelected = m->_game->getTanks(m->_selection.getPoints());
  }
  m->_selectionActive = false;
  m->_selection.clear();
}
