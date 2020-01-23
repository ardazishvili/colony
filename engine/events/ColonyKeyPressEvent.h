#ifndef COLONY_KEY_PRESS_EVENT_H
#define COLONY_KEY_PRESS_EVENT_H

#include "Event.h"

class ColonyKeyPressEvent : public KeyboardPressEvent
{
public:
  ColonyKeyPressEvent(GLFWwindow* window, int key, int scancode, int mods);

  void process(Camera* camera, EventManager* eventManager);
};

#endif
