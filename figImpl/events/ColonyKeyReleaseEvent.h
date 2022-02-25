#pragma once

#include "fig/events/Event.h"

class ColonyKeyReleaseEvent : public fig::KeyboardReleaseEvent {
 public:
  ColonyKeyReleaseEvent(int key, int scancode, int mods);
  void process(fig::Camera* camera, fig::EventManager* eventManager);
};
