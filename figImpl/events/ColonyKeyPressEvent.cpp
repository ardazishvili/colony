#include "ColonyKeyPressEvent.h"
#include "../ColonyEventManager.h"

ColonyKeyPressEvent::ColonyKeyPressEvent(int key, int scancode, int mods) :
  KeyboardPressEvent(key, scancode, mods)
{
}

void ColonyKeyPressEvent::process(Camera* camera, EventManager* eventManager)
{
  if (_key == GLFW_KEY_LEFT_SHIFT) {
    eventManager->pressKey(KeyButton::LEFT_SHIFT);
  }
}
