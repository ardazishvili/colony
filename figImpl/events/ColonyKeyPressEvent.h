#ifndef COLONY_KEY_PRESS_EVENT_H
#define COLONY_KEY_PRESS_EVENT_H

#include "../../fig/events/Event.h"

class ColonyKeyPressEvent : public KeyboardPressEvent
{
public:
  ColonyKeyPressEvent(int key, int scancode, int mods);

  void process(Camera* camera, EventManager* eventManager);
};

#endif
