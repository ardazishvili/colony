#include "ColonyMouseMoveEvent.h"
#include "../ColonyEventManager.h"

ColonyMouseMoveEvent::ColonyMouseMoveEvent(double xpos, double ypos) :
  MouseMoveEvent(xpos, ypos)
{
}

void ColonyMouseMoveEvent::process(Camera* camera, EventManager* eventManager)
{
  // TODO downcast
  auto m = dynamic_cast<ColonyEventManager*>(eventManager);
  if (m->isKeyPressed(KeyButton::LEFT_SHIFT) &&
      m->isMousePressed(MouseButton::MIDDLE)) {
    auto deltaX = _xpos - m->_middleLastPressed.x;
    auto deltaY = _ypos - m->_middleLastPressed.y;

    if (deltaY < 0) {
      camera->moveBackward();
    } else if (deltaY > 0) {
      camera->moveForward();
    }
    if (deltaX > 0) {
      camera->moveLeft();
    } else if (deltaX < 0) {
      camera->moveRight();
    }
    m->_middleLastPressed = glm::vec2(_xpos, _ypos);
  } else if (m->isMousePressed(MouseButton::MIDDLE)) {
    auto deltaX = _xpos - m->_middleLastPressed.x;
    auto deltaY = _ypos - m->_middleLastPressed.y;

    if (deltaY < 0) {
      camera->rotateUp();
    } else if (deltaY > 0) {
      camera->rotateDown();
    }
    if (deltaX > 0) {
      camera->rotateLeft();
    } else if (deltaX < 0) {
      camera->rotateRight();
    }
    m->_middleLastPressed = glm::vec2(_xpos, _ypos);
  }

  auto c = EventManager::unProject(m->_window, m->_view, m->_projection);
  if (m->_structureToBuild &&
      (m->_structureToBuildStage == BuildStage::SetAngle)) {
    float structureX = m->_structureToBuild->position().x;
    float structureY = m->_structureToBuild->position().y;
    float radianAngle = ::atan((structureY - c.y) / (structureX - c.x));
    float degreeAngle = radianAngle * 180.0f / M_PI;
    if (structureX - c.x < 0) {
      degreeAngle += 180.0f;
    }

    m->_structureToBuild->setAngle(degreeAngle);
  } else if (m->_structureToBuild &&
             (m->_structureToBuildStage == BuildStage::SetPosition)) {
    auto position =
      EventManager::unProject(m->_window, m->_view, m->_projection);
    auto maxXy = m->_terrain->getMaxXy();
    if (::abs(position.x) > maxXy || ::abs(position.y) > maxXy) {
      position = glm::vec3(maxXy, maxXy, 0.0f);
    }
    m->_structureToBuild->setPosition(
      m->_terrain->getXYZ(glm::vec2(position.x, position.y)));
  }
  if (m->_selectionActive) {
    auto tmp = c;
    tmp.z += 0.3;
    m->_selection.setEnd(tmp);
  }
}
