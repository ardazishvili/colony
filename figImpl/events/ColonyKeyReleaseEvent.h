#ifndef COLONY_KEY_RELEASE_EVENT_H
#define COLONY_KEY_RELEASE_EVENT_H

#include "../../fig/events/Event.h"

class ColonyKeyReleaseEvent : public fig::KeyboardReleaseEvent
{
public:
  ColonyKeyReleaseEvent(int key, int scancode, int mods);
  void process(fig::Camera* camera, fig::EventManager* eventManager);
};

#endif
