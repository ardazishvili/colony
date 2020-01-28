#ifndef COLONY_KEY_REPEAT_EVENT_H
#define COLONY_KEY_REPEAT_EVENT_H

#include "../../fig/events/Event.h"

class ColonyKeyRepeatEvent : public KeyboardRepeatEvent
{
public:
  ColonyKeyRepeatEvent(int key, int scancode, int mods);
  void process(Camera* camera, EventManager* eventManager);
};

#endif
