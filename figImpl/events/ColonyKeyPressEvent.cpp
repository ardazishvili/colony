#include "ColonyKeyPressEvent.h"
#include "../ColonyEventManager.h"

ColonyKeyPressEvent::ColonyKeyPressEvent(int key, int scancode, int mods) : KeyboardPressEvent(key, scancode, mods)
{
}

void ColonyKeyPressEvent::process(fig::Camera* camera, fig::EventManager* eventManager)
{
  if (_key == GLFW_KEY_LEFT_SHIFT) {
    eventManager->pressKey(fig::KeyButton::LEFT_SHIFT);
  }
}
