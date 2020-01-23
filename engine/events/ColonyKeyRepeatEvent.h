#ifndef COLONY_KEY_REPEAT_EVENT_H
#define COLONY_KEY_REPEAT_EVENT_H

#include "Event.h"

class ColonyKeyRepeatEvent : public KeyboardRepeatEvent
{
public:
  ColonyKeyRepeatEvent(GLFWwindow* window, int key, int scancode, int mods);
  void process(Camera* camera, EventManager* eventManager);
};

#endif
