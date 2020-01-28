#ifndef COLONY_KEY_RELEASE_EVENT_H
#define COLONY_KEY_RELEASE_EVENT_H

#include "../../fig/events/Event.h"

class ColonyKeyReleaseEvent : public KeyboardReleaseEvent
{
public:
  ColonyKeyReleaseEvent(int key, int scancode, int mods);
  void process(Camera* camera, EventManager* eventManager);
};

#endif
