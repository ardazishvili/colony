#include "ColonyKeyPressEvent.h"
#include "../ColonyEventManager.h"

ColonyKeyPressEvent::ColonyKeyPressEvent(GLFWwindow* window,
                                         int key,
                                         int scancode,
                                         int mods) :
  KeyboardPressEvent(window, key, scancode, mods)
{
}

void ColonyKeyPressEvent::process(Camera* camera, EventManager* eventManager)
{
  if (_key == GLFW_KEY_LEFT_SHIFT) {
    eventManager->pressKey(KeyButton::LEFT_SHIFT);
  }
}
